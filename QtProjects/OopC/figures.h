#ifndef FIGURES_H
#define FIGURES_H

#define typename( x) _Generic( ( x), \
    TTriangle : "TTriangle", \
    TTriangle* : "pointer to TTriangle" \
)

#endif // FIGURES_H

