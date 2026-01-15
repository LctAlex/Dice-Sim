FROM gcc:latest AS builder

WORKDIR /build

COPY ./src ./src

RUN g++ -static -o main src/*.cpp

FROM scratch

COPY --from=builder /build/main /dice-sim

ENTRYPOINT ["/dice-sim"]