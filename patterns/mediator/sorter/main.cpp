#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

enum Commands { LOAD, SORT, PRINT };

class Mediator {
 public:
  virtual void Notify(Commands cmd) = 0;
};

class Worker {
 public:
  void SetMediator(Mediator* mediator_) { mediator = mediator_; }

 protected:
  Mediator* mediator = nullptr;
};

class DataLoaderWorker : public Worker {
 public:
  void Load(std::string path) {
    std::fstream fs;
    fs.open(path);
    int num;
    while (!fs.eof() && fs >> num) {
      data.push_back(num);
    }
    mediator->Notify(Commands::LOAD);
  }
  std::vector<int>& Get() { return data; }

 private:
  std::vector<int> data;
};

class SortingWorker : public Worker {
 public:
  virtual void Sort(std::vector<int>& data) {}
};

class QSortWorker : public SortingWorker {
 public:
  void Sort(std::vector<int>& data) override {
    QSort(data, 0, data.size() - 1);
    mediator->Notify(Commands::SORT);
  }

 private:
  void QSort(std::vector<int>& data, std::size_t l, std::size_t r) {
    if (l < r) {
      std::size_t pos = Partition(data, l, r);
      QSort(data, l, pos);
      QSort(data, pos + 1, r);
    }
  }
  std::size_t Partition(std::vector<int>& data, std::size_t l, std::size_t r) {
    std::size_t i = l;
    std::size_t j = r;
    int pivot = data[static_cast<std::size_t>((i + j) / 2)];
    while (i <= j) {
      while (data[i] < pivot) {
        i++;
      }
      while (data[j] > pivot) {
        j--;
      }

      if (i >= j) {
        break;
      }
      std::swap(data[i++], data[j--]);
    }
    return j;
  }
};

class PrintingWorker : public Worker {
 public:
  void Print(std::vector<int>& data) {
    for (auto i : data) {
      std::cout << i << " ";
    }
    std::cout << std::endl;
  }
};

class QSortMediator : public Mediator {
 public:
  QSortMediator(DataLoaderWorker* dataloader_, QSortWorker* qsorter_,
                PrintingWorker* printer_)
      : dataloader(dataloader_), qsorter(qsorter_), printer(printer_) {
    dataloader->SetMediator(this);
    qsorter->SetMediator(this);
    printer->SetMediator(this);
  }
  void Notify(Commands cmd) override {
    switch (cmd) {
      case LOAD: {
        qsorter->Sort(dataloader->Get());
        break;
      }
      case SORT: {
        printer->Print(dataloader->Get());
      }
    }
  }

 private:
  DataLoaderWorker* dataloader;
  QSortWorker* qsorter;
  PrintingWorker* printer;
};

class Decorator : public QSortWorker {
 public:
  Decorator(QSortWorker* qsorter_) : qsorter(qsorter_) {}
  void Sort(std::vector<int>& data) { qsorter->Sort(data); }

 private:
  QSortWorker* qsorter;
};

class TimerDecorator : public Decorator {
 public:
 TimerDecorator(QSortWorker* qsorter):Decorator(qsorter){}
  void Sort(std::vector<int>& data) {
    auto start = std::chrono::high_resolution_clock::now();
    Decorator::Sort(data);
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << elapsed.count() << std::endl;
  }
};

int main() {
  DataLoaderWorker* dataloader = new DataLoaderWorker();
  QSortWorker* qsorter = new QSortWorker();
  PrintingWorker* printer = new PrintingWorker();
  Mediator* mediator = new QSortMediator(dataloader, qsorter, printer);
  dataloader->Load(std::string("file.txt"));
  TimerDecorator* timerdecorator = new TimerDecorator(qsorter);
  timerdecorator->Sort(dataloader->Get());
}
