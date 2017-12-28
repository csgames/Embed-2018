#include <catch.hpp>

#include "direction.h"


TEST_CASE("Load and dump")
{
    auto size = Direction::total();
    INFO("Total directions: " << size);

    for (uint8_t i = 0; i < size; i++)
    {
        DirectionComplex direction_complex{i};
        Direction direction{i};

        REQUIRE(std::holds_alternative<Direction>(direction_complex));
        REQUIRE(direction.dump() == std::byte{i});
        REQUIRE(direction_complex.dump() == std::byte{i});
    }
}

TEST_CASE("Direction constructor")
{
    {
        Direction direction({Direction::AFTER, Direction::CURRENT, Direction::BEFORE});
        auto iter = std::begin(direction);

        REQUIRE(*iter == Direction::AFTER);
        REQUIRE(*(++iter) == Direction::CURRENT);
        REQUIRE(*(++iter) == Direction::BEFORE);

        REQUIRE(direction.dump() == std::byte{5});
    }

    {
        Direction direction({Direction::CURRENT, Direction::AFTER, Direction::CURRENT});
        auto iter = std::begin(direction);

        REQUIRE(*iter == Direction::CURRENT);
        REQUIRE(*(++iter) == Direction::AFTER);
        REQUIRE(*(++iter) == Direction::CURRENT);

        REQUIRE(direction.dump() == std::byte{16});
    }
}

TEST_CASE("Special directions")
{
    auto size = Direction::total();

    SECTION("PC")
    {
        DirectionComplex direction{SpecialDirection::PC};
        REQUIRE(std::holds_alternative<SpecialDirection>(direction));
        REQUIRE(direction.dump() == static_cast<std::byte>(size));
    }

    SECTION("MEMBANK")
    {
        DirectionComplex direction{SpecialDirection::MEMBANK};
        REQUIRE(std::holds_alternative<SpecialDirection>(direction));
        REQUIRE(direction.dump() == static_cast<std::byte>(size + 1));
    }

    SECTION("PC from raw")
    {
        DirectionComplex direction{static_cast<uint8_t>(size)};
        REQUIRE(std::holds_alternative<SpecialDirection>(direction));
        REQUIRE(direction.dump() == static_cast<std::byte>(size));
    }

    SECTION("MEMBANK from raw")
    {
        DirectionComplex direction{static_cast<uint8_t>(size + 1)};
        REQUIRE(std::holds_alternative<SpecialDirection>(direction));
        REQUIRE(direction.dump() == static_cast<std::byte>(size + 1));
    }

    SECTION("Invalid directions")
    {
        REQUIRE_THROWS_AS(Direction{Direction::total()}, std::out_of_range);

        REQUIRE_THROWS_AS(DirectionComplex {255}, std::out_of_range);

        REQUIRE_THROWS_AS(DirectionComplex {Direction::total() + static_cast<int>(SpecialDirection::LAST_DO_NOT_USE)},
                std::out_of_range);

        REQUIRE_THROWS_AS(DirectionComplex {SpecialDirection::LAST_DO_NOT_USE}, std::out_of_range);
    }
}
