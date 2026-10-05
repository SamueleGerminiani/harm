#include "CoiInfo.hh"

#include "message.hh"

namespace harm {

//H6: not implemented yet (stubs so that the acceptance tests compile and fail)
std::shared_ptr<CoiInfo> CoiInfo::load(const std::string &, const TracePtr &) {
  messageError("CoiInfo::load is not implemented");
  return nullptr;
}
bool CoiInfo::knows(const std::string &) const { return false; }
const CoiInfo::Source *CoiInfo::source(const std::string &,
                                       const std::string &) const {
  return nullptr;
}
std::vector<LeafOffset>
leafOffsets(const expression::TemporalExpressionPtr &) {
  return {};
}
CoiMetrics computeCoiMetrics(const expression::TemporalExpressionPtr &,
                             const CoiInfo &) {
  return CoiMetrics{-1, -1, 0};
}

} // namespace harm
