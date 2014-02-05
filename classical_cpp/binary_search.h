#ifndef __WTS_BINARY_SEARCH__
#define __WTS_BINARY_SEARCH__
#include <functional>
#include <iterator>

namespace wts {

// Default template arguments for a function template are a C++11 extension.
//
// It seems C++ cannot deduce the type of the parameter from default function arguments in
// function templates.
//
// template <typename IT, typename COMP>
// IT binary_search(IT begin,
// 		 IT end,
// 		 const typename std::iterator_traits<IT>::value_type &val,
// 		 COMP comp = std::less<typename std::iterator_traits<IT>::value_type>()) {

template <typename IT, typename COMP>
IT binary_search(IT begin,
		 IT end,
		 const typename std::iterator_traits<IT>::value_type &val,
		 COMP comp) {

	IT fail = end;
	while (end > begin) {
		IT it = begin + (end - begin) / 2;
		if (comp(val, *it)) {
			end = it;
		}
		else if (comp(*it, val)) {
			begin = ++it;
		}
		else {
			return it;
		}
	}

	return fail;
}

template <typename IT>
IT binary_search(IT begin,
		 IT end,
		 const typename std::iterator_traits<IT>::value_type &val) {
	return wts::binary_search(begin, end, val, std::less<typename std::iterator_traits<IT>::value_type>());
}

template <typename IT, typename COMP>
IT lower_bound(IT begin,
	       IT end,
	       const typename std::iterator_traits<IT>::value_type &val,
	       COMP comp) {
	while (end > begin) {
		IT it = begin + (end - begin) / 2;
		if (comp(*it, val)) { // *it < val
			begin = ++it;
		}
		else { // *it >= val
			end = it;
		}
	}
	return end;
}

template <typename IT>
IT lower_bound(IT begin,
	       IT end,
	       const typename std::iterator_traits<IT>::value_type &val) {
	return wts::lower_bound(begin, end, val, std::less<typename std::iterator_traits<IT>::value_type>());
}

} // namespace wts

#endif
