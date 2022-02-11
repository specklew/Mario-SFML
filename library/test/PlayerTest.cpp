#include <boost/test/unit_test.hpp>

#include "Entities/Entity.h"
#include "Entities/EntityFactory.h"
#include "Entities/Goomba.h"
#include "Entities/PPlant.h"
#include "Resources/Resource.h"
#include "Resources/ResourceRegistry.h"
#include "Tiles/Tile.h"
#include "Game.h"
#include "Level.h"
#include "Player.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include "Resources/ResourceRegistry.h"
#include "AnimatedGif.h"
#include "Level.h"
#include "Enemies/Enemy.h"

BOOST_AUTO_TEST_SUITE(PlayerTest)
    BOOST_AUTO_TEST_CASE(CHECK_PLAYER_HP) {
        Player * player = new Player(0,0);
        BOOST_REQUIRE_EQUAL(player->getHP(), 5);
        delete player;
    }
    BOOST_AUTO_TEST_CASE(test2) {
        Player * player = new Player(0,0);w
        BOOST_REQUIRE_EQUAL(player->getPos().x, 0);
        BOOST_REQUIRE_EQUAL(player->getPos().y, 0);
        delete player;
    }
    BOOST_AUTO_TEST_CASE(test3) {

        Player * player = new Player(0,0);
        player->getPlayerBounds();
        Game * game = Game::GetInstance();
        Level * level = game->getCurrentLevel();
        ResourceID lol3;
        lol3=ResourceID::COIN_ENTITY_ID;
       // for (auto  enemy : level->entities)
        //{
         //   if(enemy->getID()==lol3) {
          //      if ( player->getPlayerBounds().intersects(enemy->sprite.getGlobalBounds()))
          //      {
          //          BOOST_REQUIRE_EQUAL(player->CoinTouched(), 1);
           //     }
           // }
       // }

        delete level;

    }



BOOST_AUTO_TEST_SUITE_END()