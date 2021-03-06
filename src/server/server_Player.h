#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "server_Worm.h"
#include "server_Armory.h"
#include <stdlib.h>
#include <map>
#include <utility>
#include <vector>

/* Representación de un Jugador. Tiene un grupo de gusanos que conforma su
 * ejército, y un armamento que comparten todos los gusanos. Internamente
 * tiene un gusano seleccionado el cual va a utilizar en su turno.
 * No es copiable.
 */
class Player {
private:
  std::vector<Worm*> worms;
  size_t selected_index;
  Armory* armory;

  // No copiable.
  Player(const Player&) = delete;
  Player& operator=(const Player&) = delete;

public:
  // Constructor. Recibe un puntero al armory que va a equipar.
  explicit Player(Armory* armory);

  // Agrega el gusano al ejército.
  void add_worm(Worm* worm);

  // Devuelve un puntero al gusano seleccionado.
  Worm* get_selected_worm();

  // Selecciona el proximo gusano.
  void select_next_worm();

  // Devuelve un booleano indicando si tiene algún gusano vivo.
  bool has_worms_alive();

  // Devuelve un vector con todos los worms del jugador.
  std::vector<Worm*> get_worms();

  // Teletransporta el gusano seleccionado a la coordenada (X,Y) indicada.
  bool teletransport_actual_worm(double x, double y);

  // Devuelve un booleano indicando si la teletransportacion fue utilizada
  // desde la última vez que se preguntó.
  bool was_teletransportation_used();

  // Devuelve la cantidad de teletransportaciones que quedan.
  int get_teletransportation_munitions();

  // Utiliza la dinamita con el gusano seleccionado.
  bool use_dynamite();

  // Devuelve la cantidad de dinamitas que quedan.
  int get_dynamite_munitions();

  // Descuenta la cantidad de milisegundos recibida para la explosión de la
  // dinamita.
  void discount_dynamite_time(float t);

  // Devuelve un booleano indicando si la dinamita está activa.
  bool is_dynamite_active();

  // Devuelve un float indicando la posición horizontal de la dinamita activa.
  float get_dynamite_horizontal_position();

  // Devuelve un float indicando la posición vertical de la dinamita activa.
  float get_dynamite_vertical_position();

  // Devuelve un float indicando la cantidad de milisegundos hasta la explosión
  // de la dinamita activa. Si no está activa, devuelve 7000.
  float get_dynamite_time_to_explosion();

  // Utiliza el teledirigido centrado, si es posible, en la posición x recibida.
  bool use_radiocontrolled(float x);

  // Devuelve un booleano indicando si el teledirigido está activo.
  bool is_radiocontrolled_active();

  // Devuelve la cantidad de teledirigidos que quedan.
  int get_radiocontrolled_munitions();

  // Devuelve un vector de pares X,Y indicando las posiciones de todos los
  // teledirigidos activos.
  std::map<size_t, std::pair<float, float>> get_radiocontrolled_positions();

  // Revisa, para cada munición activa del teledirigido, si está colisionando
  // con algún objeto y en caso que sea verdadero se encarga de hacerlo explotar
  // y eliminar dicha munición. Devuelve un vector con el id de las municiones
  // que explotaron.
  std::vector<size_t> check_radiocontrolled_explosions();

  // Devuelve un booleano indicando si el jugador tiene un arma activa.
  bool has_an_active_weapon();

  // Destructor.
  ~Player();
};

#endif //__PLAYER_H__
