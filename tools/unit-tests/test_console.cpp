#include <gtest/gtest.h>
#include "../../ONRL/src/console.h"

TEST(ConsoleTest, CreateConsole) {
    gfx::Console console(80, 25, "LiberationMono-Bold.ttf", 12); // example font path

    // You can check if render and window_display can be called without crash
    EXPECT_NO_THROW(console.render());
    EXPECT_NO_THROW(console.window_display());
}

TEST(ConsoleTest, SetAndGetGlyph) {
    gfx::Console console(10, 10, "LiberationMono-Bold.ttf", 12);

    gfx::Console::glyph_t g{'A', sf::Color::Red, sf::Color::Black};
    console.set_glyph(0, 0, g);

    auto result = console.get_glyph(0, 0);
    EXPECT_EQ(result.c, 'A');
    EXPECT_EQ(result.fg, sf::Color::Red);
    EXPECT_EQ(result.bg, sf::Color::Black);
}
