#include "main.h"

void MoveParticles(const int nr_Particles, Particle* const partikel,
                   const float dt) {
  // Abschwaechung als zusaetzlicher Abstand, um Singularitaet und
  // Selbst-Interaktion zu vermeiden
  const float softening = 1e-20;

  // Schleife ueber alle Partikel
  for (int i = 0; i < nr_Particles; i++) {
    Particle partikelI = partikel[i];
    // Kraftkomponenten (x,y,z) der Kraft auf aktuellen Partikel (i)
    float Fx = 0, Fy = 0, Fz = 0;

    // Schleife ueber die anderen Partikel die Kraft auf Partikel i ausueben
    for (int j = 0; j < nr_Particles; j++) {
      // Gravitationsgesetz
      // Berechne Abstand der Partikel i und j
      const float dx = partikel[j].x - partikelI.x;
      const float dy = partikel[j].y - partikelI.y;
      const float dz = partikel[j].z - partikelI.z;
      const float drSquared = dx * dx + dy * dy + dz * dz + softening;

      // Vorab-Berechnung der Kraftkomponente
      const float invDrPower32 = 1.0f / (drSquared * sqrt(drSquared));

      // Addiere Kraftkomponenten zur Netto-Kraft
      Fx += dx * invDrPower32;
      Fy += dy * invDrPower32;
      Fz += dz * invDrPower32;
    }

    // Berechne Aenderung der Geschwindigkeit des Partikel i durch einwirkende
    // Kraft
    partikel[i].vx += dt * Fx;
    partikel[i].vy += dt * Fy;
    partikel[i].vz += dt * Fz;
  }

  // Bewege Partikel entsprechend der aktuellen Geschwindigkeit
  for (int i = 0; i < nr_Particles; i++) {
    partikel[i].x += partikel[i].vx * dt;
    partikel[i].y += partikel[i].vy * dt;
    partikel[i].z += partikel[i].vz * dt;
  }
}

void MoveParticlesRef(const int nr_Particles, Particle* const partikel,
                      const float dt) {
  // Schleife ueber alle Partikel
  for (int i = 0; i < nr_Particles; i++) {
    // Kraftkomponenten (x,y,z) der Kraft auf aktuellen Partikel (i)
    float Fx = 0, Fy = 0, Fz = 0;

    // Schleife ueber die anderen Partikel die Kraft auf Partikel i ausueben
    for (int j = 0; j < nr_Particles; j++) {
      // Abschwaechung als zusaetzlicher Abstand, um Singularitaet und
      // Selbst-Interaktion zu vermeiden
      const float softening = 1e-20;

      // Gravitationsgesetz
      // Berechne Abstand der Partikel i und j
      const float dx = partikel[j].x - partikel[i].x;
      const float dy = partikel[j].y - partikel[i].y;
      const float dz = partikel[j].z - partikel[i].z;
      const float drSquared = dx * dx + dy * dy + dz * dz + softening;
      const float drPower32 = pow(drSquared, 3.0 / 2.0);

      // Addiere Kraftkomponenten zur Netto-Kraft
      Fx += dx / drPower32;
      Fy += dy / drPower32;
      Fz += dz / drPower32;
    }

    // Berechne Aenderung der Geschwindigkeit des Partikel i durch einwirkende
    // Kraft
    partikel[i].vx += dt * Fx;
    partikel[i].vy += dt * Fy;
    partikel[i].vz += dt * Fz;
  }

  // Bewege Partikel entsprechend der aktuellen Geschwindigkeit
  for (int i = 0; i < nr_Particles; i++) {
    partikel[i].x += partikel[i].vx * dt;
    partikel[i].y += partikel[i].vy * dt;
    partikel[i].z += partikel[i].vz * dt;
  }
}
