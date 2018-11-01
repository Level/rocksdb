const fs = require('fs')
const path = require('path')

const leveldbPath = path.join(__dirname, '/../deps/rocksdb/rocksdb')
const buildVersionPath = path.join(leveldbPath, '/util/build_version.cc')

// Read build_version.cc.in
let buildVersionCC = fs.readFileSync(`${buildVersionPath}.in`, {
  encoding: 'utf8'
})

// Replace both variables
// The Git SHA is hardcoded in deps/leveldb/leveldb.gyp
buildVersionCC = buildVersionCC.replace('@@GIT_SHA@@', process.argv[2])
buildVersionCC = buildVersionCC.replace(
  '@@GIT_DATE_TIME@@',
  new Date().toISOString()
)

// Write build_version.cc
fs.writeFileSync(buildVersionPath, buildVersionCC)
