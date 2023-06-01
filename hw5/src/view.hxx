#pragma once

#include "model.hxx"

#include <string>

class View
{
public:
    /// View dimensions will use `int` coordinates.
    using Dimensions = ge211::Dims<int>;

    /// View positions will use `int` coordinates.
    using Position = ge211::Posn<int>;

    /// View rectangles will use `int` coordinates.
    using Rectangle = ge211::Rect<int>;

    /// Constructs a view that knows about the given model.
    explicit View(Model const&);

    // We added an argument here so that the
    // controller can communicate UI state (such as a mouse or
    // cursor position):
    void draw(ge211::Sprite_set& set, Position mouse_posn);

    Dimensions initial_window_dimensions() const;

    std::string initial_window_title() const;
    /*
    static Player
    get_current(Model const& model);
    */
    /*
    static Move_map nxt(Model const& model);
    */

    // TODO: Add any public member functions you need.
    //ge211::Circle_sprite const ball_sprite;



View::Position
board_to_screen(Model::Position) const;
Model::Position
screen_to_board(View::Position) const;

Player
winner(Model const& model){
    return model.winner();
}



private:
    Model const& model_;

    // TODO: Add any additional private members you need, such as helper
    // functions or sprites.

    ge211::Circle_sprite const dark_sprite;
    ge211::Circle_sprite const light_sprite;
    ge211::Rectangle_sprite const board_sprite;
    ge211::Rectangle_sprite const to_be_changed;
    ge211::Circle_sprite const hover;
    ge211::Circle_sprite const hover2;
    ge211::Rectangle_sprite const gameover;
    ge211::Rectangle_sprite const tie;


};
