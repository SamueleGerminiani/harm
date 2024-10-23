#include <vector>
namespace harm {

//MatchList is a list of matches, it can contain multiple matches, but only one potential false match
struct MatchList {
  //if the value is negative, it is a false match (only one false match is possible, in this case _longestFalseMatch remains zero)
  //if the value is positive, it is a true match (there can be multiple true matches)
  //if the value is == ep, it is a unknown match
  //0 is for empty matches
  std::vector<int> _matches;

  //containts the longest false match: when all the matches fail, this is the length of the longest false match. Used to keep track of when a formula ultimately fails
  int _longestFalseMatch = 0;

  int operator[](size_t i) const { return _matches[i]; }
  size_t size() const { return _matches.size(); }
  void push_back(int i) { _matches.push_back(i); }
  int front() const { return _matches.front(); }
  void clear() { _matches.clear(); }
  void sort() { std::sort(_matches.begin(), _matches.end()); }
  bool empty() const { return _matches.empty(); }
  auto begin() const { return _matches.begin(); }
  auto end() const { return _matches.end(); }
  int back() const { return _matches.back(); }
  //insert with iterators
  void insert(const std::vector<int>::const_iterator &where,
              const std::vector<int>::const_iterator &begin,
              const std::vector<int>::const_iterator &end) {
    _matches.insert(where, begin, end);
  }
  bool is_sorted() const {
    return std::is_sorted(_matches.begin(), _matches.end());
  }
  void remove_duplicates() {
    if (_matches.size() < 2)
      return;
    std::sort(_matches.begin(), _matches.end());
    auto last = std::unique(_matches.begin(), _matches.end());
    _matches.erase(last, _matches.end());
  }
};
} // namespace harm
