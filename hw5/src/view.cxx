#include "view.hxx"

// Convenient type aliases:
using Color = ge211::Color;
using Sprite_set = ge211::Sprite_set;

// You can change this or even determine it some other way:
static int const grid_size = 36;
//Helper functions

Player get_current(Model const& model){
    return model.turn();
}

static ge211::Color const dark {0, 0, 0};
static ge211::Color const light {255, 255, 127};
static ge211::Color const boardc {0, 255, 0};
static ge211::Color const changed {120, 0, 0};
static ge211::Color const over {255, 255, 255};
static ge211::Color const tiee {200, 200, 200};
View::View(Model const& model)
        : model_(model), dark_sprite(17, dark), light_sprite(17, light),
        board_sprite({34,34}, boardc), to_be_changed({34,36}, changed), hover(9,dark ), hover2(9, light), gameover({34,34}, over), tie({34,34}, tiee )

        // You may want to add sprite initialization here
{ }

View::Position
View::board_to_screen(Model::Position logical)  const
{
    return {logical.x * 36, logical.y * 36};
}
Model::Position
View::screen_to_board(Model::Position physical) const
{
    return {int(floor(physical.x / 36)), int(floor(physical.y / 36))};
}



void View::draw(Sprite_set& set, Position mouse_posn) {
    //if mouse is hovering, add the pointer thing, and color all valid moves if they are there
    //set.add_sprite(board_sprite, {0,0}, 0)
    //we want to add dark colored sprites on every square occupied by dark player

    for (Position p: model_.all_positions()) {
        Position screen = board_to_screen(p);
        //Position board = screen_to_board(p);
        set.add_sprite(board_sprite, screen, 0);

        if (model_.turn() == Player::dark) {
            set.add_sprite(hover, mouse_posn, 2);
        } else if (model_.turn() == Player::light) {
            set.add_sprite(hover2, mouse_posn, 2);
        }

        if (model_[p] == Player::dark) {
            set.add_sprite(dark_sprite, screen, 3);

        }
            //add light sprites
        else if (model_[p] == Player::light) {
            set.add_sprite(light_sprite, screen, 3);
        }
        //when mouse is hovering on psn

        const Move *move = model_.find_move(screen_to_board(mouse_posn));
        if (move) {
            Position_set flips = move->second;
            for (Position po: flips) {
                set.add_sprite(to_be_changed, board_to_screen(po), 2);
            }
        }


    }
    for (Position p: model_.all_positions()) {
        if (model_.is_game_over()) {
            if (model_.winner() == Player::dark) {


                    if (model_[p] == Player::light) {
                        // std::cout<<"adding winning sprite";
                        set.add_sprite(gameover, board_to_screen(p), 1);
                    }

            } else if (model_.winner() == Player::light) {

                for (Position pi: model_.all_positions()) {
                    if (model_[pi] == Player::dark) {
                        //std::cout<<"adding winning sprite";
                        set.add_sprite(gameover, board_to_screen(pi), 1);
                    }
                }
            } else if (model_.winner() == Player::neither) {
                for (Position pi: model_.all_positions()) {
                    //std::cout<<"adding winning sprite";
                    set.add_sprite(tie, board_to_screen(pi), 1);
                }
                return;
            }

        }
    }


}


View::Dimensions
View::initial_window_dimensions() const
{
    // You can change this if you want:
    return grid_size * model_.all_positions().dimensions();
}

std::string
View::initial_window_title() const
{
    // You can change this if you want:
    return "Reversi Yangu";
}

