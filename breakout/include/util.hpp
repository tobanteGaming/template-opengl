#pragma once

/**
 * @brief Handy function for avoiding unused variables warning.
 */
template <typename... Types>
void ignoreUnused(Types&&...) noexcept
{
}