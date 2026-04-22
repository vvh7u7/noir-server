# ---- build stage ----
FROM gcc:13 AS build

WORKDIR /app

RUN apt-get update && apt-get install -y \
    cmake \
    git \
    libsqlite3-dev \
    && rm -rf /var/lib/apt/lists/*

COPY . .

RUN mkdir build && cd build && \
    cmake .. && \
    make -j$(nproc)

# ---- runtime stage ----
FROM debian:bookworm-slim

WORKDIR /app

RUN apt-get update && apt-get install -y \
    libsqlite3-0 \
    && rm -rf /var/lib/apt/lists/*

COPY --from=build /app/build/NoirServer /app/NoirServer

EXPOSE 8080

CMD ["./NoirServer"]
