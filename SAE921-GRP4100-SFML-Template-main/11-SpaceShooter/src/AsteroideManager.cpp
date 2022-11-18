#include "AsteroideManager.h"

AsteroideManager::AsteroideManager() {
}

void AsteroideManager::FindAsteroidetoDestroy() {
    std::erase_if(currentAsteroide, [](Asteroide& a) {return a.isTouched; });
}
