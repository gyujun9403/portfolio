CMAKE_MINIMUM_REQUIRED( VERSION 3.4.3 )

# IO멀티플렉싱 모델 라이브러리
SET(MODEL_DIR /MultiplexingModel)
SET(IMODEL_HEADER ${MODEL_DIR}/IMultiplexingModel.hpp)
SET(EPOLL_HEADER ${MODEL_DIR}/Model_Epoll/EpollModel.hpp)

#SET(MODEL_LIB )

# 패킷 라이브러리
SET(PACKET_DIR /Packet)
SET(PACKET_HEADERS ${PACKET_DIR}/PacketBase.hpp)

# 서버 라이브러리
SET(SERVER_DIR /Server)
SET(SERVER_HEADERS ${PACKET_DIR}/Server.hpp)

# 세션 라이브러리
SET(SESSION_DIR /Session)
SET(SESSION_CONTAINER_HEADERS ${SESSION_DIR}/SessionContainer.hpp)
SET(SESSION_HEADERS ${SESSION_DIR}/SESSION_LIB.hpp)
#SET(SESSION_LIB ${SESSION_DIR}/SessionContainer.hpp)

# 싱크 라이브러리
SET(SYNC_DIR /Sync)
SET(ISYNC_HEADER ${SYNC_DIR}/IMultiplexingModel.hpp)
SET(SYNC_HEADERS ${SYNC_DIR}/PacketBase.hpp)

SET(ALL_HEADERS ${IMODEL_HEADER} ${} ${} ${})