#include "EnemyManager.h"

EnemyManager::EnemyManager() {
    spawnIntPos = 0;
    if (!sfxEnemyDeath.loadFromFile("data/Sound/EnemyFire.ogg")) {
        std::cout << "SoundEffect failed to load" << std::endl;
    }
}

void EnemyManager::AddEnemy(b2World& world) {
    if (timerBetweenEnemy.GetMilliseconds() > timeBetweenEnemy) {
        if (spawnIntPos == 0) {
            currentEnemy.emplace_back(world, 0, -200, 1);
            spawnIntPos = 1;
        }
        else if (spawnIntPos == 1) {
            currentEnemy.emplace_back(world, 900, -100, -1);
            spawnIntPos = 2;
        }
        else {
            currentEnemy.emplace_back(world, 0, -300, 1);
            spawnIntPos = 0;
        }
        timerBetweenEnemy.Reset();
    }
}

void::EnemyManager::FindEnemytoDestroy() {
    std::erase_if(currentEnemy, [](Enemy& a) {return a.isTouched; });
    //currentAsteroide.erase(touchingAsteroide, currentAsteroide.end());
}

void EnemyManager::PlayDestroySound() {
    for (auto& enemy : currentEnemy) {
        if (enemy.isTouched) {
            sound.setBuffer(sfxEnemyDeath);
            sound.play();
        }
    }
}

void::EnemyManager::Render(sf::RenderWindow& window) {
    PlayDestroySound();
    FindEnemytoDestroy();

    for (auto& enemy : currentEnemy) {
        enemy.Update();

        window.draw(enemy.enemySprite);
        window.draw(enemy.enemySprite);
        window.draw(enemy.enemyHealthBar);

        enemy.FindAsteroidetoDestroy();
        for (auto& asteroid : enemy.currentAsteroide) {
            asteroid.Update();
            window.draw(asteroid);
        }
    }
}
