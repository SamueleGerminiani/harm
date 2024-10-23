#install third_party libraries
file(COPY ${SpotLib} DESTINATION ${IP}/harm/lib FOLLOW_SYMLINK_CHAIN)
file(COPY ${BddxLib} DESTINATION ${IP}/harm/lib FOLLOW_SYMLINK_CHAIN)
file(COPY ${AntrLib} DESTINATION ${IP}/harm/lib FOLLOW_SYMLINK_CHAIN)
file(COPY ${BoostLib} DESTINATION ${IP}/harm/lib FOLLOW_SYMLINK_CHAIN)
