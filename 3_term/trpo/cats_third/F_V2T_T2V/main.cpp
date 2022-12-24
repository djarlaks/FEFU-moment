#include <iostream>
#include <tuple>
#include <vector>

#include "v2t_t2v.h"

#define check_t(expr, type) static_assert(std::is_same_v<decltype(expr), type>)

using std::cout;
using std::decay_t;
using std::declval;
using std::endl;
using std::is_same_v;
using std::pair;
using std::tuple;
using std::tuple_element_t;
using std::vector;

template <typename VectorOfTuple>
auto v2t(VectorOfTuple&& vec_tuple) {
  return VectorToTuple(std::forward<VectorOfTuple>(vec_tuple));
}

template <typename TupleOfVector>
auto t2v(TupleOfVector&& tuple_vec) {
  return TupleToVector(std::forward<TupleOfVector>(tuple_vec));
}

template <typename... Ts>
constexpr void easy_check() {
  using vec_in = vector<tuple<Ts...>>;
  using cvec_in = const vector<tuple<Ts...>>;

  using tpl_in = tuple<vector<decay_t<Ts>>...>;
  using ctpl_in = const tuple<vector<decay_t<Ts>>...>;
  using crctpl_in = const tuple<const vector<decay_t<Ts>>&...>;

  if constexpr (sizeof...(Ts) == 1) {
    using vec_solo = vector<std::tuple_element_t<0, tuple<decay_t<Ts>...>>>;

    check_t(v2t(vec_in()), vec_solo);
    check_t(t2v(tpl_in()), vec_solo);
    check_t(t2v(v2t(vec_in())), vec_solo);
    check_t(v2t(t2v(tpl_in())), vec_solo);

    vec_in v;
    check_t(t2v(v2t(v)), vec_solo);
    tpl_in t;
    check_t(v2t(t2v(t)), vec_solo);

    cvec_in cv;
    check_t(t2v(v2t(cv)), vec_solo);
    ctpl_in ct;
    check_t(v2t(t2v(ct)), vec_solo);

    vector<decay_t<Ts>...> v1;
    crctpl_in crct{v1};
    check_t(v2t(t2v(crct)), vec_solo);
    check_t(v2t(t2v(crctpl_in{v1})), vec_solo);
  } else if constexpr (sizeof...(Ts) == 2) {
    using vec_pair = vector<pair<decay_t<Ts>...>>;
    using pair_vec = pair<vector<decay_t<Ts>>...>;

    check_t(v2t(vec_in()), pair_vec);

    check_t(t2v(tpl_in()), vec_pair);

    check_t(v2t(t2v(tpl_in())), pair_vec);
    check_t(v2t(t2v(pair_vec())), pair_vec);
    check_t(t2v(v2t(vec_in())), vec_pair);
    check_t(t2v(v2t(vec_pair())), vec_pair);

    pair_vec pv;
    check_t(v2t(t2v(pv)), pair_vec);
    vec_pair vp;
    check_t(t2v(v2t(vp)), vec_pair);

    const pair_vec cpv;
    check_t(v2t(t2v(cpv)), pair_vec);
    const vec_pair cvp;
    check_t(t2v(v2t(cvp)), vec_pair);

    using t1 = tuple_element_t<0, tuple<Ts...>>;
    using t2 = tuple_element_t<1, tuple<Ts...>>;
    vector<decay_t<t1>> v1;
    vector<decay_t<t2>> v2;
    crctpl_in crct{v1, v2};
    check_t(v2t(t2v(crct)), pair_vec);
    check_t(v2t(t2v(crctpl_in{v1, v2})), pair_vec);
  } else {
    using vec = vector<tuple<decay_t<Ts>...>>;
    using tpl = tuple<vector<decay_t<Ts>>...>;

    check_t(t2v(v2t(t2v(v2t(t2v(v2t(vec_in())))))), vec);

    check_t(v2t(t2v(v2t(t2v(v2t(t2v(tpl_in())))))), tpl);

    vec_in v;
    check_t(t2v(v2t(t2v(v2t(t2v(v2t(v)))))), vec);
    tpl_in t;
    check_t(v2t(t2v(v2t(t2v(v2t(t2v(t)))))), tpl);

    cvec_in cv;
    check_t(t2v(v2t(t2v(v2t(t2v(v2t(cv)))))), vec);
    ctpl_in ct;
    check_t(v2t(t2v(v2t(t2v(v2t(t2v(ct)))))), tpl);
  }
}

[[noreturn]] void fail() {
  std::cout << -1 << std::endl;
  exit(0);
}

int main() {
  easy_check<int>();
  easy_check<double&>();
  easy_check<const char>();
  easy_check<const float&>();
  easy_check<const short&&>();

  easy_check<int, double>();
  easy_check<const double, char&>();
  easy_check<char, const float&>();
  easy_check<const float, const short&>();
  easy_check<const short&&, const int&&>();

  easy_check<int, double, short>();
  easy_check<const short&, int&, double>();
  easy_check<const double&&, const short&, int&>();

  easy_check<const char&&, signed char&&, const unsigned char&&, float,
             const double, int, const unsigned int>();
  easy_check<const char&, const signed char&&, const unsigned char&&,
             const float&, const double, const int, const unsigned int&&>();

  {
    vector<tuple<int>> v;
    for (int i = 0; i < 100; ++i) v.push_back(tuple<int>{i});
    vector<int> single = v2t(v);
    for (int i = 0; i < 100; ++i)
      if (single[i] != i) fail();
    single = t2v(single);
    for (int i = 0; i < 100; ++i)
      if (single[i] != i) fail();
  }

  {
    vector<tuple<int, int>> v;
    for (int i = 0; i < 100; ++i) v.push_back(tuple<int, int>{i, -i});
    auto [v1, v2] = v2t(v);
    for (int i = 0; i < 100; ++i)
      if (v1[i] != i || v2[i] != -i) fail();
    auto vp = t2v(pair<vector<int>, vector<int>>{v1, v2});
    for (int i = 0; i < 100; ++i)
      if (vp[i].first != i || vp[i].second != -i) fail();
  }

  {
    vector<tuple<int, int, int>> v;
    for (int i = 0; i < 100; ++i)
      v.push_back(tuple<int, int, int>{i, -i, i << 1});
    auto [v1, v2, v3] = v2t(v);
    for (int i = 0; i < 100; ++i)
      if (v1[i] != i || v2[i] != -i || v3[i] != i << 1) fail();
    auto vt = t2v(tuple<vector<int>&, vector<int>&, vector<int>&>{v1, v2, v3});
    for (int i = 0; i < 100; ++i)
      if (std::get<0>(vt[i]) != i || std::get<1>(vt[i]) != -i ||
          std::get<2>(vt[i]) != i << 1)
        fail();
  }

  cout << 0 << endl;
  return 0;
}
