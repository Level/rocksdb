const fs = require('fs')
const path = require('path')

const leveldbPath = path.join(__dirname, '/../deps/rocksdb/rocksdb')
const buildVersionPath = path.join(leveldbPath, '/util/build_version.cc')
const outputPath = process.argv[2]

// Read build_version.cc.in
let buildVersionCC = fs.readFileSync(`${buildVersionPath}.in`, {
  encoding: 'utf8'
})

// Replace both variables
// We can't rely on git being available so we set sha to "n/a"
buildVersionCC = buildVersionCC.replace('@@GIT_SHA@@', 'n/a')
buildVersionCC = buildVersionCC.replace(
  '@@GIT_DATE_TIME@@',
  new Date().toISOString()
)

// Write build_version.cc
fs.writeFileSync(outputPath, buildVersionCC)
