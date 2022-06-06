#pragma once
#include "texture.h"

#include <memory>

// Поддерживаемые виды фигур: прямоугольник и эллипс
enum class ShapeType { RECTANGLE, ELLIPSE};

class Shape {
public:
    // Фигура после создания имеет нулевые координаты и размер,
    // а также не имеет текстуры
    explicit Shape(ShapeType type) : type_(type) {
        
    }

    void SetPosition(Point pos) {
        pos_ = pos;
    }

    void SetSize(Size size) {
        size_ = size;
    }

    void SetTexture(std::shared_ptr<Texture> texture) {
        texture_ = std::move(texture);
    }
   
    // Рисует фигуру на указанном изображении
	// В зависимости от типа фигуры должен рисоваться либо эллипс, либо прямоугольник
    // Пиксели фигуры, выходящие за пределы текстуры, а также в случае, когда текстура не задана,
    // должны отображаться с помощью символа точка '.'
    // Части фигуры, выходящие за границы объекта image, должны отбрасываться.
    void Draw(Image& image) const {
        
        for (int y = 0; y < size_.height; ++y) {
            for (int x = 0; x < size_.width; ++x) {

                int xx = x + pos_.x;
                int yy = y + pos_.y;

                if ((yy >= 0) && (xx >= 0) && (yy < (int)image.size()) && (xx < (int)image[0].size())) {

                    if (type_ == ShapeType::RECTANGLE && IsPointInRectangle({ x,y }, size_)) {
                        if (texture_) {
                            image[yy][xx] = texture_->GetPixelColor({ x,y });
                        }
                        else image[yy][xx] = '.';
                    }
                    if (type_ == ShapeType::ELLIPSE && IsPointInEllipse({ x,y }, size_)) {
                        if (texture_) {
                            image[yy][xx] = texture_->GetPixelColor({ x,y });
                        }
                        else image[yy][xx] = '.';
                    }
                }
            }
        }
    }

private:
    Size size_;
    Point pos_;
    ShapeType type_;
    std::shared_ptr<Texture> texture_;
};