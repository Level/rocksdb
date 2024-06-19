const test = require('tape')
const tempy = require('tempy')
const leveldown = require('..')
const suite = require('abstract-leveldown/test')

module.exports = suite.common({
  test: test,
  factory: function (location = tempy.directory()) {
    const db = leveldown(location)
    const _open = db.open.bind(db)
    db.open = (optionOrCallback, callbackOrNull) => {
      let callback
      const options = {
        awsAccessKeyId: process.env.AWS_ACCESS_KEY_ID,
        awsSecretAccessKey: process.env.AWS_SECRET_ACCESS_KEY,
        awsRegion: 'ap-northeast-2',
        awsEndpointUrl: process.env.AWS_ENDPOINT_URL,
        awsBucketName: 'rockset.rocksdb-test-bucket',
        awsObjectPrefix: location,
        useSSL: false
      }

      if (typeof optionOrCallback === 'function') {
        callback = optionOrCallback
      } else {
        Object.assign(options, optionOrCallback)
        callback = callbackOrNull
      }
      return _open(options, callback)
    }
    return db
  },

  // Opt-in to new tests
  clear: true,
  getMany: true,

  // abstract-leveldown test suite options
  createIfMissing: false
})
