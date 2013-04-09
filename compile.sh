PROJECT_NAME="gbot"
PROJECT_OUTPUT="gbot"
if [ -f "$PROJECT_OUTPUT" ]
then
    rm "$PROJECT_OUTPUT"
fi
gcc \
    -lcurl \
    -lpthread \
    -lstdc++ \
    main.cpp -o "$PROJECT_OUTPUT"
if [ -f "$PROJECT_OUTPUT" ]
then
    ./"$PROJECT_OUTPUT"
fi
