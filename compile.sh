rm cbot
gcc \
    -lcurl \
    -lpthread \
    -lstdc++ \
    main.cpp -o cbot
./cbot
