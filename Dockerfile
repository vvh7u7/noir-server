# =========================
# Build stage
# =========================
FROM gcc:14 AS build

WORKDIR /app

ARG CMAKE_VERSION=4.3.1

RUN apt-get update && apt-get install -y \
    curl \
    unzip \
    ninja-build \
    pkg-config \
    libssl-dev \
    libsqlite3-dev \
    git \
    && rm -rf /var/lib/apt/lists/*

# install modern CMake
RUN curl -L \
    https://github.com/Kitware/CMake/releases/download/v${CMAKE_VERSION}/cmake-${CMAKE_VERSION}-linux-x86_64.tar.gz \
    -o cmake.tar.gz && \
    tar -xzf cmake.tar.gz && \
    mv cmake-${CMAKE_VERSION}-linux-x86_64 /opt/cmake && \
    ln -s /opt/cmake/bin/cmake /usr/local/bin/cmake && \
    ln -s /opt/cmake/bin/ctest /usr/local/bin/ctest && \
    rm cmake.tar.gz

COPY . .

RUN cmake -B build -S . -G Ninja \
    -DCMAKE_BUILD_TYPE=Release && \
    cmake --build build -j$(nproc)

# =========================
# Runtime stage
# =========================
FROM debian:bookworm-slim

WORKDIR /app

RUN apt-get update && apt-get install -y \
    libsqlite3-0 \
    libssl3 \
    ca-certificates \
    && rm -rf /var/lib/apt/lists/*

COPY --from=build /app/build/NoirServer /app/NoirServer

EXPOSE 10000

CMD ["./NoirServer"]
