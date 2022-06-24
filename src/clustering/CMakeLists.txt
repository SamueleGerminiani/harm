#############################################
# Configuration.
#############################################

SET(NAME clustering)


#############################################
# Sources.
#############################################
SET (CLUSTERING_SRCS
    src/Hierarchical.cc
    src/KDE.cc
    src/Kmeans.cc
    )

#############################################
# Targets.
#############################################
add_library(${NAME} ${CLUSTERING_SRCS})

target_include_directories( ${NAME} PUBLIC include/)

