#pragma once

#include "typelist.h"

template <typename TList, typename TargetType>
struct IndexOf;

template <typename TargetType>
struct IndexOf<NullType, TargetType> {
  static constexpr unsigned int pos = -1;
};

template <typename Tail, typename TargetType>
struct IndexOf<TypeList<TargetType, Tail>, TargetType> {
  static constexpr unsigned int pos = 0;
};

template <typename Head, typename Tail, typename TargetType>
struct IndexOf<TypeList<Head, Tail>, TargetType> {
  static constexpr unsigned int tmp = IndexOf<Tail, TargetType>::pos;
  static constexpr unsigned int pos = (tmp == -1 ? -1 : tmp + 1);
};