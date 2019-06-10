#pragma once

namespace tobanteGaming
{
/**
 * @brief Handy function for avoiding unused variables warning.
 */
template<typename... Types>
void ignoreUnused(Types&&... /*unused*/) noexcept
{
}

}  // namespace tobanteGaming