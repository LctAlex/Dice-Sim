FROM gcc:latest AS builder

WORKDIR /build

COPY ./src ./src

RUN g++ -static -o main src/main.cpp

FROM scratch

# Dam COPY in container doar la fisierul binar
COPY --from=builder /build/main /main

ENTRYPOINT ["/main"]