#pragma once

#include "UpdatableObject.hpp"
#include "Shape3D.hpp"

/// @brief Reprezentuje gracza w œwiecie gry 3D.
///
/// Klasa obs³uguje logikê renderowania, ruchu, kolizji oraz stanu ¿ycia gracza.
/// Dziedziczy zarówno po `UpdatableObject`, jak i `Shape3D`, dziêki czemu mo¿e byæ aktualizowana i rysowana w scenie.
class Player : public UpdatableObject, public Shape3D {
public:

	/// @brief Rysuje gracza w scenie.
	/// @param view Macierz widoku kamery.
	void draw(const glm::mat4& view) override;

	/// @brief Aktualizuje logikê gracza.
	/// @param delta Czas delta w milisekundach.
	/// @param input Dane wejœciowe gracza (klawiatura, mysz).
	/// @param manager WskaŸnik na mened¿era silnika.
	void update(float delta, const InputMap& input, EngineManager* manager) override;

	/// @brief Konstruktor gracza.
	/// @param playerModel WskaŸnik na model graficzny gracza.
	/// @param size Rozmiar gracza.
	/// @param startpos Pozycja pocz¹tkowa w przestrzeni.
	Player(Shape3D* playerModel, double size, glm::vec3 startpos);

	/// @brief Zwraca aktualn¹ pozycjê gracza.
	/// @return Pozycja gracza jako wektor 3D.
	glm::vec3 getPos() const;

	/// @brief Zwraca rozmiar gracza.
	/// @return Rozmiar jako liczba zmiennoprzecinkowa.
	double getSize() const;

	/// @brief Oznacza gracza jako trafionego (np. przez kolizjê).
	void hit();

protected:
	Shape3D* playerModel; ///< WskaŸnik na model 3D gracza.
	bool dead = false;    ///< Flaga okreœlaj¹ca, czy gracz zosta³ trafiony.
	double size;          ///< Rozmiar gracza (promieñ, œrednica itp.).
	glm::vec3 pos;        ///< Aktualna pozycja gracza.
};
