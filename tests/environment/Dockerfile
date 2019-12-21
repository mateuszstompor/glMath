FROM gcc:9.1.0 AS ENVIRONMENT
RUN apt update && apt install -y cmake
RUN apt install -y valgrind
COPY ./tests/environment/install_gtest.sh /var/tmp/gtest/install_gtest.sh
RUN /var/tmp/gtest/install_gtest.sh
COPY ./CMakeLists.txt /var/tmp/glMath/CMakeLists.txt
COPY ./glMath /var/tmp/glMath/glMath/
COPY ./tests /var/tmp/glMath/tests
WORKDIR /var/tmp/glMath/
RUN cmake . -DBUILD_TESTING=ON
RUN make && make install
ENTRYPOINT ["/var/tmp/glMath/glMath_tests"]
