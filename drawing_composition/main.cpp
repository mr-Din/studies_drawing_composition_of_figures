#include "canvas.h"
#include "shapes.h"

#include <iostream>
#include <string>
#include <memory>
#include <cassert>
#include <sstream>

using namespace std;


std::unique_ptr<Texture> MakeTextureCow() {
    Image image = { R"(^__^            )",  //
                   R"((oo)\_______    )",  //
                   R"((__)\       )\/\)",  //
                   R"(    ||----w |   )",  //
                   R"(    ||     ||   )" };
    return std::make_unique<Texture>(move(image));
}

std::unique_ptr<Texture> MakeTextureSolid(Size size, char pixel) {
    Image image(size.height, std::string(size.width, pixel));
    return std::make_unique<Texture>(move(image));
}

std::unique_ptr<Texture> MakeTextureCheckers(Size size, char pixel1, char pixel2) {
    Image image(size.height, std::string(size.width, pixel1));

    for (int i = 0; i < size.height; ++i) {
        for (int j = 0; j < size.width; ++j) {
            if ((i + j) % 2 != 0) {
                image[i][j] = pixel2;
            }
        }
    }

    return std::make_unique<Texture>(move(image));
}

void TestCpp() {
    Canvas canvas(Size{ 77, 17 });

    // Буква "C" как разность двух эллипсов, один из которых нарисован цветом фона
    canvas.AddShape(ShapeType::ELLIPSE, { 2, 1 }, { 30, 15 },
        MakeTextureCheckers({ 100, 100 }, 'c', 'C'));
    canvas.AddShape(ShapeType::ELLIPSE, { 8, 4 }, { 30, 9 }, MakeTextureSolid({ 100, 100 }, ' '));

    // Горизонтальные чёрточки плюсов
    auto h1 = canvas.AddShape(ShapeType::RECTANGLE, { 54, 7 }, { 22, 3 },
        MakeTextureSolid({ 100, 100 }, '+'));
    canvas.DuplicateShape(h1, { 30, 7 });

    // Вертикальные чёрточки плюсов
    auto v1 = canvas.DuplicateShape(h1, { 62, 3 });
    canvas.ResizeShape(v1, { 6, 11 });
    canvas.DuplicateShape(v1, { 38, 3 });

    std::stringstream output;
    canvas.Print(output);

    const auto answer
        = "###############################################################################\n"
        "#                                                                             #\n"
        "#            cCcCcCcCcC                                                       #\n"
        "#        CcCcCcCcCcCcCcCcCc                                                   #\n"
        "#      cCcCcCcCcCcCcCcCcCcCcC          ++++++                  ++++++         #\n"
        "#    CcCcCcCcCcCc                      ++++++                  ++++++         #\n"
        "#   CcCcCcCcC                          ++++++                  ++++++         #\n"
        "#   cCcCcCc                            ++++++                  ++++++         #\n"
        "#  cCcCcC                      ++++++++++++++++++++++  ++++++++++++++++++++++ #\n"
        "#  CcCcCc                      ++++++++++++++++++++++  ++++++++++++++++++++++ #\n"
        "#  cCcCcC                      ++++++++++++++++++++++  ++++++++++++++++++++++ #\n"
        "#   cCcCcCc                            ++++++                  ++++++         #\n"
        "#   CcCcCcCcC                          ++++++                  ++++++         #\n"
        "#    CcCcCcCcCcCc                      ++++++                  ++++++         #\n"
        "#      cCcCcCcCcCcCcCcCcCcCcC          ++++++                  ++++++         #\n"
        "#        CcCcCcCcCcCcCcCcCc                                                   #\n"
        "#            cCcCcCcCcC                                                       #\n"
        "#                                                                             #\n"
        "###############################################################################\n";

    assert(answer == output.str());
}

void TestCow() {
    Canvas canvas{ {18, 5} };

    canvas.AddShape(ShapeType::RECTANGLE, { 1, 0 }, { 16, 5 }, MakeTextureCow());

    std::stringstream output;
    canvas.Print(output);

    // clang-format off
    // Здесь уместно использовать сырые литералы, т.к. в текстуре есть символы '\'
    const auto answer =
        R"(####################)""\n"
        R"(# ^__^             #)""\n"
        R"(# (oo)\_______     #)""\n"
        R"(# (__)\       )\/\ #)""\n"
        R"(#     ||----w |    #)""\n"
        R"(#     ||     ||    #)""\n"
        R"(####################)""\n";
    // clang-format on
    cout << answer << endl << output.str() << endl;
    assert(answer == output.str());
}

void TestCow2() {
    Canvas canvas{ {18, 5} };

    canvas.AddShape(ShapeType::RECTANGLE, { -1, -1 }, { 19,8 }, MakeTextureCow());

    std::stringstream output;
    canvas.Print(output);
    cout << output.str() << endl;
}
void MyTest() {
    Canvas canvas{ {50, 25} };

    canvas.AddShape(ShapeType::RECTANGLE, { 1, 1 }, { 20,12 }, MakeTextureCheckers({ 60,60 }, '0', '0'));
    canvas.AddShape(ShapeType::ELLIPSE, { 12, 4 }, { 24,12 }, MakeTextureCheckers({60,60},'-','-'));
    canvas.AddShape(ShapeType::ELLIPSE, { 20, 12 }, { 30,12 }, MakeTextureCheckers({ 20,10 }, 'x', 'x'));

    std::stringstream output;
    canvas.Print(output);
    cout << output.str() << endl;
}

int main()
{
    TestCow();
    TestCow2();
    MyTest();
    TestCpp();
}
