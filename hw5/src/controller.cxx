#include "controller.hxx"

Controller::Controller(int size)
        : Controller(size, size)
{ }

Controller::Controller(int width, int height)
        : model_(width, height),
          view_(model_)

{ }

void Controller::on_mouse_move(ge211::Posn<int> pos){

   mouse_psn_ = pos;
}
void Controller::on_mouse_down(ge211::Mouse_button btn, View::Position pos){

    Model::Position p = view_.screen_to_board(mouse_psn_);

    const Move* move = model_.find_move(p);
    if (move && !model_.is_game_over() && btn == ge211::Mouse_button::left ) {

        model_.play_move(p);

    }


}
//&&

void
Controller::draw(ge211::Sprite_set& sprites)
{
    // TODO this code should give the most recently updated mouse
    //  position to the draw() function when calling it.

    view_.draw(sprites, mouse_psn_);
}
View::Dimensions
Controller::initial_window_dimensions() const
{
    return view_.initial_window_dimensions();
}

std::string
Controller::initial_window_title() const
{
    return view_.initial_window_title();
}

