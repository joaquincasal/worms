#include <iomanip>
#include <string>
#include "client_DrawableFactory.h"

DrawableFactory::DrawableFactory(SocketProtocol& sp, \
                                  SafeQueue<IDrawable*>& _safe_queue) : \
                                  socket_protocol(sp),
                                  safe_queue(_safe_queue) {
  connected = true;
}

void DrawableFactory::create_start_turn_drawable(){
  safe_queue.push(new StartTurnDrawable());
}

void DrawableFactory::create_end_turn_drawable(){
  safe_queue.push(new EndTurnDrawable());
}

void DrawableFactory::create_turn_time_drawable(){
  double turn_time = socket_protocol.receive_double_value();
  safe_queue.push(new TurnTimeDrawable(turn_time));
}

void DrawableFactory::create_worm_drawable(){
  size_t id = socket_protocol.receive_numeric_value();
  size_t life_points = socket_protocol.receive_numeric_value();
  double x = socket_protocol.receive_double_value();
  double y = socket_protocol.receive_double_value();
  int angle = socket_protocol.receive_numeric_value() * -1;
  bool is_facing_right = (bool)socket_protocol.receive_numeric_value();
  int team = socket_protocol.receive_numeric_value();
  int movement_state = socket_protocol.receive_numeric_value();
  bool is_the_selected_worm = (bool)socket_protocol.receive_numeric_value();
  x = meters_to_pixels(x);
  y = meters_to_pixels(y);
  y = adapt_y_coordinate(y);
  safe_queue.push(new WormDrawable(id, life_points, x, y, angle, \
                                   is_facing_right, team, movement_state,\
                                   is_the_selected_worm));
}

void DrawableFactory::create_worm_death_drawable(){
  size_t id = socket_protocol.receive_numeric_value();
  int team = socket_protocol.receive_numeric_value();
  safe_queue.push(new WormDeathDrawable(id, team));
}


void DrawableFactory::create_beam_drawable(){
  double x = socket_protocol.receive_double_value();
  double y = socket_protocol.receive_double_value();
  size_t length = socket_protocol.receive_numeric_value();
  size_t width = socket_protocol.receive_numeric_value();
  size_t angle = socket_protocol.receive_numeric_value() * -1;
  x = meters_to_pixels(x);
  y = meters_to_pixels(y);
  y = adapt_y_coordinate(y);
  length = meters_to_pixels(length);
  width = meters_to_pixels(width);
  safe_queue.push(new BeamDrawable(x, y, length, width, angle));
}

void DrawableFactory::create_stage_drawable(){
  size_t width = socket_protocol.receive_numeric_value();
  size_t height = socket_protocol.receive_numeric_value();
  std::string background = socket_protocol.receive_string();
  width = meters_to_pixels(width);
  height = meters_to_pixels(height);
  scenario_height = height;
  safe_queue.push(new StageDrawable(width, height, background));
}

void DrawableFactory::create_dynamite_drawable(){
  double x = socket_protocol.receive_double_value();
  double y = socket_protocol.receive_double_value();
  double time_to_explosion = socket_protocol.receive_double_value();
  x = meters_to_pixels(x);
  y = meters_to_pixels(y);
  y = adapt_y_coordinate(y);
  safe_queue.push(new DynamiteDrawable(x, y, time_to_explosion));
}

void DrawableFactory::create_dynamite_explosion_drawable(){
  safe_queue.push(new DynamiteExplosionDrawable());
}

void DrawableFactory::create_radiocontrolled_drawable(){
  size_t id = (size_t)(socket_protocol.receive_numeric_value());
  double x = socket_protocol.receive_double_value();
  double y = socket_protocol.receive_double_value();
  x = meters_to_pixels(x);
  y = meters_to_pixels(y);
  y = adapt_y_coordinate(y);
  safe_queue.push(new RadiocontrolledDrawable(id, x, y));
}

void DrawableFactory::create_radiocontrolled_explosion_drawable(){
  size_t id = (size_t)(socket_protocol.receive_numeric_value());
  safe_queue.push(new RadiocontrolledExplosionDrawable(id));
}

void DrawableFactory::create_you_win_drawable(){
  safe_queue.push(new YouWinDrawable());
}

void DrawableFactory::create_you_lose_drawable(){
  safe_queue.push(new YouLoseDrawable());
}

void DrawableFactory::create_munitions_drawable(){
  int dynamite_m = socket_protocol.receive_numeric_value();
  int radiocontrolled_m = socket_protocol.receive_numeric_value();
  int teletransportation_m = socket_protocol.receive_numeric_value();
  safe_queue.push(new MunitionsDrawable(dynamite_m, radiocontrolled_m,\
                                        teletransportation_m));
}


void DrawableFactory::create_closed_connection_drawable(){
  safe_queue.push(new ClosedConnectionDrawable());
}

void DrawableFactory::create_drawable(){
  char code = socket_protocol.receive();
  switch (code) {
    case PROTOCOL_TURN_START:
      create_start_turn_drawable();
      break;
    case PROTOCOL_TURN_END:
      create_end_turn_drawable();
      break;
    case PROTOCOL_TURN_TIME:
      create_turn_time_drawable();
      break;
    case PROTOCOL_WORM_INFO:
      create_worm_drawable();
      break;
    case PROTOCOL_WORM_DEATH_NOTIF:
      create_worm_death_drawable();
      break;
    case PROTOCOL_STAGE_INFO:
      create_stage_drawable();
      break;
    case PROTOCOL_BEAM_INFO:
      create_beam_drawable();
      break;
    case PROTOCOL_DYMAMITE_INFO:
      create_dynamite_drawable();
      break;
    case PROTOCOL_DYMAMITE_EXPLOSION:
      create_dynamite_explosion_drawable();
      break;
    case PROTOCOL_RADIOCONTROLLED_INFO:
      create_radiocontrolled_drawable();
      break;
    case PROTOCOL_RADIOCONTROLLED_EXPLOSION_INFO:
      create_radiocontrolled_explosion_drawable();
      break;
    case PROTOCOL_YOU_WIN_NOTIF:
      create_you_win_drawable();
      break;
    case PROTOCOL_YOU_LOSE_NOTIF:
      create_you_lose_drawable();
      break;
    case PROTOCOL_MUNITIONS_INFO:
      create_munitions_drawable();
      break;
    case PROTOCOL_CLOSED_CON:
      this->stop();
      create_closed_connection_drawable();
      break;
  }
}

void DrawableFactory::run(){
  while (connected) {
    create_drawable();
  }
}

bool DrawableFactory::is_connected(){
  return connected;
}


void DrawableFactory::stop(){
  connected = false;
  socket_protocol.shutdown(SHUT_RDWR);
}

double DrawableFactory::meters_to_pixels(double meters){
  return meters * METERS_TO_PIXELS_CONVERSION;
}

double DrawableFactory::adapt_y_coordinate(double y){
  return y * -1 + scenario_height;
}

double DrawableFactory::get_scenario_height(){
  return scenario_height;
}
