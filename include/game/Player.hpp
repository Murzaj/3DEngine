#pragma once

#include "UpdatableObject.hpp"
#include "Shape3D.hpp"

/// @brief Reprezentuje gracza w �wiecie gry 3D.
///
/// Klasa obs�uguje logik� renderowania, ruchu, kolizji oraz stanu �ycia gracza.
/// Dziedziczy zar�wno po `UpdatableObject`, jak i `Shape3D`, dzi�ki czemu mo�e by� aktualizowana i rysowana w scenie.
class Player : public UpdatableObject, public Shape3D {
public:

	/// @brief Rysuje gracza w scenie.
	/// @param view Macierz widoku kamery.
	void draw(const glm::mat4& view) override;

	/// @brief Aktualizuje logik� gracza.
	/// @param delta Czas delta w milisekundach.
	/// @param input Dane wej�ciowe gracza (klawiatura, mysz).
	/// @param manager Wska�nik na mened�era silnika.
	void update(float delta, const InputMap& input, EngineManager* manager) override;

	/// @brief Konstruktor gracza.
	/// @param playerModel Wska�nik na model graficzny gracza.
	/// @param size Rozmiar gracza.
	/// @param startpos Pozycja pocz�tkowa w przestrzeni.
	Player(Shape3D* playerModel, double size, glm::vec3 startpos);

	/// @brief Zwraca aktualn� pozycj� gracza.
	/// @return Pozycja gracza jako wektor 3D.
	glm::vec3 getPos() const;

	/// @brief Zwraca rozmiar gracza.
	/// @return Rozmiar jako liczba zmiennoprzecinkowa.
	double getSize() const;

	/// @brief Oznacza gracza jako trafionego (np. przez kolizj�).
	void hit();

protected:
	Shape3D* playerModel; ///< Wska�nik na model 3D gracza.
	bool dead = false;    ///< Flaga okre�laj�ca, czy gracz zosta� trafiony.
	double size;          ///< Rozmiar gracza (promie�, �rednica itp.).
	glm::vec3 pos;        ///< Aktualna pozycja gracza.
};
