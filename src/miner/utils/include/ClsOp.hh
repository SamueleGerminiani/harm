
namespace harm {
/** @enum ClsOp
 *  @brief Operator for a numeric expression (clustering): 
 *  Range: l <= numeric <= r;
 *  E: numeric == r;
 *  GE: numeric >= r;
 *  LE: numeric <= r.
 */
enum class ClsOp { Range = 0, E, GE, LE };
} // namespace harm
