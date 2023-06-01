#include "model.hxx"

using namespace ge211;

Model::Model(int size)
        : Model(size, size)
{ }

Model::Model(int width, int height)
        : board_({width, height})
{
    // TODO: initialize `next_moves_` to `turn_`'s available moves

    //how to find available moves, is it just the set of all positions


    compute_next_moves_();


}

Model::Rectangle
Model::all_positions() const
{
    return board_.all_positions();
}

Player
Model::operator[](Position pos) const
{
    return board_[pos];
}

const Move*
Model::find_move(Position pos) const
{
    auto i = next_moves_.find(pos);

    if (i == next_moves_.end()) {
        // Nothing was found, so return NULL (nullptr in C++)
        return nullptr;
    } else {
        // Dereferences the iterator to get the value then returns a pointer
        // to that value. This is safe as the pointer is to a value living
        // within the `next_moves_` structure.
        return &(*i);
    }
}

void
Model::play_move(Position pos)
{
    if (is_game_over()) {
        throw Client_logic_error("Model::play_move: game over");
    }

    const Move* movep = find_move(pos);
    if (movep == nullptr) { // check if there was no such move
        throw Client_logic_error("Model::play_move: no such move");
    }

    // TODO: actually execute the move, advance the turn, refill
    // `next_moves_`, etc.
    really_play_move_(*movep);




}

//
// BELOW ARE HELPER FUNCTIONS
// Our tests will run on the public functions, not the helper functions
// However, these will be extremely useful in writing the above functions
//

Position_set
Model::find_flips_(Position current, Dimensions dir) const {


    Position_set result;
    Position next = current + dir;
    //Player curr = turn();
    //iterate until the conditions are not true
    //for (;;)
    /*
    while ((board_.good_position(next)) && board_[next] != Player::neither) {
        //check if position contains an opposing player
        if (board_[current] == other_player(curr) ) {


            result[next] = true;
            next = next + dir;
        }
        //check if the current position is not occupied by an opp
        if (board_[current] == curr) {
            return result;
        }

    }*/

    while( board_.good_position(next) && board_[next] == other_player(turn_)){
        result[next] = true;
        next = next + dir;

    }
    if (!board_.good_position(next) || board_[next] != turn_){
        return{};
    }




    return result;
}

Position_set
Model::evaluate_position_(Position pos) const
{

    if (Model::operator[](pos) != Player::neither){
        return {};
    }
    Position_set p_moves;
    for (Dimensions d : Board::all_directions()){
        Position_set flips = find_flips_(pos, d);
        p_moves |= flips;
    }
    //Adding the current position tot e
    if (p_moves.empty()){
        return {};
    }
    else{
        p_moves[pos] = true;
    }
    return p_moves;


}

void
Model::compute_next_moves_()
{
    next_moves_.clear();
    for (Position p : board_.center_positions()) {
        if (board_[p] == Player::neither){
            next_moves_[p]= {p};
        }
    }
    if (!next_moves_.empty()){
        //std::cout<<"this ran";
        return;
    }

        for(Position p : board_.all_positions()){
            Position_set nxt_moves = evaluate_position_(p);
            if (!nxt_moves.empty()){
                next_moves_[p] = nxt_moves;
            }

        }


}

bool
Model::advance_turn_()
{

    turn_ = other_player(turn_);
    compute_next_moves_();
    if (next_moves_.empty()){
        //std::cout<< "this rain";
        return false ;
    }
    else {
        return true;
    }



}

void
Model::set_game_over_()
{
    //this may choose the wrong winner if we dont count the total nu,mber of spots occupied by each player
    size_t l_count = board_.count_player(Player::light);
    size_t d_count = board_.count_player(Player::dark);
    if (l_count > d_count){
        winner_ = Player::light;
    }
    else if (d_count > l_count){
        winner_ = Player::dark;
    }
    else {
        winner_ = Player::neither;
    }
    turn_ = Player::neither;
}

void
Model::really_play_move_(Move move)
{
    board_.set_all(move.second, turn_) ;
    if (advance_turn_()){
        //not sure if merely calling advance turn changes the turn to the next player automatically
        return;
      //turn_ = other_player(turn_);
    }
    if (advance_turn_()){
        //turn_ = other_player(turn_);
        //how to get the other player to play again
        return;
    }

    set_game_over_();


}
