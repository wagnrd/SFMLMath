#include <SFML/Graphics.hpp>
#include <SFMLMath.hpp>
#include <filesystem>
#include <iostream>

enum class CalculationType {
    None,
    Multiplication,
    Addition,
    Subtraction,
    Normal,
    Reflect,
    Projection,
    Rotate,
    Invert,
    Length,
    Distance,
    Dot,
};

int main() {
    int x = 1200;
    int y = 700;
    auto mid = sf::Vector2f(x/2, y/2);
    auto l1 = mid;
    sf::RenderWindow sfmlWin(sf::VideoMode(x, y),
                             "SFML Math Showcase");
    sfmlWin.setFramerateLimit(60);

    sf::Text overlayText;
    sf::Font font;
    auto path = std::filesystem::current_path();
    if (!font.loadFromFile(path.generic_string() + "/myfont.ttf")) {
        return -1;
    }

    sf::Text description;

    overlayText.setFont(font);

    std::string desc = "l1 = mid\nl2 = mousePos - mid\nline = {l1, l2 + l1}\n\n";
    description.setFont(font);
    description.setPosition(10, 250);
    description.setCharacterSize(15);
    description.setString(desc);

    overlayText.setString("Select mode, press:\n1 - None\n2 - Multiplication\n3 - Addition\n4 - Subtraction\n5 - Normal between points\n6 - Reflect\n7 - Projection\n8 - Rotate\n9 - Invert\n0 - Length\nQ - Distance\nW - Dot product\nPress ESC to exit");
    overlayText.setPosition(10, 10);
    overlayText.setCharacterSize(12);

    CalculationType calcType = CalculationType::None;

    while (sfmlWin.isOpen()) {
        sfmlWin.clear(sf::Color::Black);
        sf::Event e;
        while (sfmlWin.pollEvent(e)) {
            if (e.type == sf::Event::Closed) {
                sfmlWin.close();
            }
            if (e.type == sf::Event::KeyPressed) {
                if (e.key.code == sf::Keyboard::Escape) {
                    sfmlWin.close();
                }
                if (e.key.code == sf::Keyboard::Num1) {
                    calcType = CalculationType::None;
                    description.setString(desc);
                }
                if (e.key.code == sf::Keyboard::Num2) {
                    calcType = CalculationType::Multiplication;
                }
                if (e.key.code == sf::Keyboard::Num3) {
                    calcType = CalculationType::Addition;
                }
                if (e.key.code == sf::Keyboard::Num4) {
                    calcType = CalculationType::Subtraction;
                }
                if (e.key.code == sf::Keyboard::Num5) {
                    calcType = CalculationType::Normal;
                }
                if (e.key.code == sf::Keyboard::Num6) {
                    calcType = CalculationType::Reflect;
                }
                if (e.key.code == sf::Keyboard::Num7) {
                    calcType = CalculationType::Projection;
                }
                if (e.key.code == sf::Keyboard::Num8) {
                    calcType = CalculationType::Rotate;
                }
                if (e.key.code == sf::Keyboard::Num9) {
                    calcType = CalculationType::Invert;
                }
                if (e.key.code == sf::Keyboard::Num0) {
                    calcType = CalculationType::Length;
                }
                if (e.key.code == sf::Keyboard::Q) {
                    calcType = CalculationType::Distance;
                }
                if (e.key.code == sf::Keyboard::W) {
                    calcType = CalculationType::Dot;
                }
            }
        }
        auto mousePos = sf::Vector2f{sf::Mouse::getPosition(sfmlWin)};
        auto l2 = mousePos - mid;

        switch (calcType) {
            case CalculationType::None:
                break;
            case CalculationType::Multiplication:
                l2 = l2 * 2;
                description.setString(desc + "Modify the vector with multiplication: \nl2 = l2 * 2");
                break;
            case CalculationType::Addition:
                l2 = l2 + sf::Vector2f{50, 50};
                description.setString(desc + "Modify the vector with addition: \nl2 = l2 + {50, 50}");
                break;
            case CalculationType::Subtraction:
                l2 = l2 - sf::Vector2f{50, 50};
                description.setString(desc + "Modify the vector with subtraction: \nl2 = l2 - {50, 50}");
                break;
            case CalculationType::Normal:
                l2 = sf::normalBetweenPoints(mousePos, mid) * 100;
                description.setString(desc + "Normal between mid and Mouse: \nl2 = sf::normalBetweenPoints(mousePos, mid) * 100");
                break;
            case CalculationType::Reflect: {

                description.setString(desc + "Reflect the mouse position over the line y = 0: \nl2 = sf::reflect(mousePos, {0, 1})");
                sf::Vertex line[] = {
                        sf::Vertex(mid + sf::Vector2f{200.0f, 0.0f}, sf::Color::Blue),
                        sf::Vertex(mid - sf::Vector2f{200.0f, 0.0f}, sf::Color::Blue),
                };
                sfmlWin.draw(line, 2, sf::Lines);

                auto normal = sf::normalBetweenPoints(mid - sf::Vector2f{200.0f, 0.0f}, mid + sf::Vector2f{200.0f, 0.0f});

                sf::Vertex line2[] = {
                        sf::Vertex(mid, sf::Color::Blue),
                        sf::Vertex(mid + normal * 50, sf::Color::Blue),
                };
                sfmlWin.draw(line2, 2, sf::Lines);
                l2 = sf::reflect(l2, normal);
                break;
            }
            case CalculationType::Projection: {
                auto prjLine1 = mid + sf::Vector2f{200.0f, 0.0f};
                auto prjLine2 = mid - sf::Vector2f{200.0f, 0.0f};
                sf::Vertex line[] = {
                        sf::Vertex(prjLine1, sf::Color::Blue),
                        sf::Vertex(prjLine2, sf::Color::Blue),
                };
                sfmlWin.draw(line, 2, sf::Lines);

                l2 = sf::projection(l2, prjLine2 - prjLine1);
                description.setString(desc + "Project the mouse position over the line y = 0: \nl2 = sf::projection(l2, prjLine2 - prjLine1)");
                break;
            }
            case CalculationType::Rotate:
                l2 = sf::rotate(l2, 45);
                description.setString(desc + "Rotate the vector by 45 degrees: \nl2 = sf::rotate(l2, 45)");
                break;
            case CalculationType::Invert:
                l2 = sf::invert(l2);
                description.setString(desc + "Invert the vector: \nl2 = sf::invert(l2)");
                break;
            case CalculationType::Length: {
                auto len = sf::getLength(l2);
                description.setString(desc + "Get the length of the vector: \nl2 = sf::length(l2)");
                sf::RectangleShape rect;
                rect.setPosition(mid + sf::Vector2f{0.0f, 50.0f});
                rect.setSize(sf::Vector2f{len, 10.0f});
                sfmlWin.draw(rect);
                break;
            }
            case CalculationType::Distance: {
                auto len = sf::distance(mid, mousePos);
                description.setString(desc + "Get the distance between the mouse and the mid vector: \nl2 = sf::distance(mid, mousePos)");
                sf::RectangleShape rect;
                rect.setPosition(mid + sf::Vector2f{0.0f, 50.0f});
                rect.setSize(sf::Vector2f{len, 10.0f});
                sfmlWin.draw(rect);
                break;
            }
            case CalculationType::Dot: {
                auto len1 = sf::Vector2f {1, 1} * l2;
                auto len2 = sf::Vector2f {0, 1} * l2;
                auto len3 = sf::Vector2f {1, 0} * l2;
                description.setString(desc + "Get dot product between l2 and three separate axis vectors: \nlen1 = sf::Vector2f {1, 1} * l2\nlen2 = sf::Vector2f {0, 1} * l2\nlen3 = sf::Vector2f {1, 0} * l2");
                sf::RectangleShape rect;
                rect.setPosition(mid + sf::Vector2f{0.0f, 50.0f});
                rect.setSize(sf::Vector2f{len1, 10.0f});
                sfmlWin.draw(rect);

                rect.setPosition(mid + sf::Vector2f{0.0f, 70.0f});
                rect.setSize(sf::Vector2f{len2, 10.0f});
                sfmlWin.draw(rect);

                rect.setPosition(mid + sf::Vector2f{0.0f, 90.0f});
                rect.setSize(sf::Vector2f{len3, 10.0f});
                sfmlWin.draw(rect);
                break;
            }
        }

        sf::Vertex line[] = {
                sf::Vertex(l1, sf::Color::Green),
                sf::Vertex(l1 + l2, sf::Color::Green),
        };
        sfmlWin.draw(line, 2, sf::Lines);
        sf::Vertex mouseLine[] = {
                sf::Vertex(l1, sf::Color::Red),
                sf::Vertex(mousePos, sf::Color::Red),
        };
        sfmlWin.draw(mouseLine, 2, sf::Lines);
        sfmlWin.draw(overlayText);
        sfmlWin.draw(description);

        sfmlWin.display();
    }
    return 0;
}
