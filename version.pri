# Need to discard STDERR so get path to NULL device
win32 {
    NULL_DEVICE = NUL # Windows doesn't have /dev/null but has NUL
} else {
    NULL_DEVICE = /dev/null
}

# Trying to get version from git tag
GIT_VERSION = $$system(git describe --abbrev=0 2> $${NULL_DEVICE})
GIT_VERSION ~= s/v/""
GIT_VERSION ~= s/-/"."
#message(GIT_VERSION = $${GIT_VERSION})

# Extracting the major version
VER_MAJ = $${GIT_VERSION}
VER_MAJ ~= s/\.\w+//
#message(VER_MAG = $${VER_MAJ})

# Extracting the minor version
VER_MIN = $${GIT_VERSION}
VER_MIN ~= s/^\d+\.//
VER_MIN ~= s/\.\w+//
#message(VER_MIN = $${VER_MIN})

# Extracting the patch version
VER_PAT = $${GIT_VERSION}
VER_PAT ~= s/^\d+\.\d+\.//
VER_PAT ~= s/\.\w+//
#message(VER_PAT = $${VER_PAT})

# Trying to get count commit since a last tag
VER_BUILD = $$system(git rev-list $(git describe --abbrev=0)..HEAD --count)

# Trying to get current git branch name
BRANCH = $$system(git branch --show-current)
VER_BRANCH = $${BRANCH}
#message(VER_BRANCH = $${VER_BRANCH})
VER_BRANCH ~= s/^feat_\w+/feature
VER_BRANCH ~= s/^fix_\w+/fix
VER_BRANCH ~= s/^release_\d+\.\d+\.\d+/release
#message(VER_BRANCH = $${VER_BRANCH})

# Set the version format depending on the git branch
VERSION = $${VER_MAJ}.$${VER_MIN}.$${VER_PAT}-a$${VER_BUILD}$${BRANCH}
equals(VER_BRANCH, master) {
    VERSION = $${VER_MAJ}.$${VER_MIN}.$${VER_PAT}
}
equals(VER_BRANCH, develop) {
    VERSION = $${VER_MAJ}.$${VER_MIN}.$${VER_PAT}-b$${VER_BUILD}
}
equals(VER_BRANCH, release) {
    VERSION = $${VER_MAJ}.$${VER_MIN}.$${VER_PAT}-r$${VER_BUILD}
}
equals(VER_BRANCH, fix) {
    VERSION = $${VER_MAJ}.$${VER_MIN}.$${VER_PAT}-r$${VER_BUILD}
}
equals(VER_BRANCH, feature) {
    VERSION = $${VER_MAJ}.$${VER_MIN}.$${VER_PAT}-a$${VER_BUILD}_$${BRANCH}
}
