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
        awsAccessKeyId: 'rlbOQElLK2jQ41aXP1Jt',
        awsSecretAccessKey: 'mrgnvEvu5h1kl4H7B1sXx7yGYtU4Z1fDmomSx6tz',
        awsRegion: 'ap-northeast-2',
        awsEndpointUrl: 'localhost:9000',
        awsBucketName: 'rockset.rocksdb-test-bucket',
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
