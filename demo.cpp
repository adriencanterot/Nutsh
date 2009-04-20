#include "demo.h"
#include <phonon>

int main() {
    Phonon::MediaObject media;
    media.setCurrentSource("http://lallaa");
    media.play();
    //media.pause() et stop() sont aussi de la partie;
}
