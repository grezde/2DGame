#include "SceneScaling.h"
#include "Game.h"

void VideoLikeScene::onWindowResize(sf::Vector2i size)
{
	float nx = size.x, ny = size.y;
	float ox = Game::WIDTH, oy = Game::HEIGHT;
	transform = sf::Transform::Identity;
	transform.scale(ox / nx, oy / ny, 0, 0);
	if (nx / ny < ox / oy)
		transform.scale(nx / ox, nx / ox, nx / 2, ny / 2);
	else
		transform.scale(ny / oy, ny / oy, nx / 2, ny / 2);
	transform.translate((nx - ox)/2, (ny - oy)/2);
}

void TopRightScene::onWindowResize(sf::Vector2i size)
{
	float nx = size.x, ny = size.y;
	float ox = Game::WIDTH, oy = Game::HEIGHT;
	transform = sf::Transform::Identity;
	transform.scale(ox / nx, oy / ny, 0, 0);
	if (nx / ny < ox / oy) {
		transform.translate(0, (oy * nx/ox - ny) / 2);
		transform.scale(nx / ox, nx / ox, nx / 2, ny / 2);
	}
	else {
		transform.translate((nx- ox * ny / oy) / 2, 0);
		transform.scale(ny / oy, ny / oy, nx / 2, ny / 2);
	}
	transform.translate((nx - ox) / 2, (ny - oy) / 2);
}
