const test = require('tape')
const testCommon = require('./common')

test('prefix_extractor', function (t) {
  const db = testCommon.factory()

  t.test('setup', function (t) {
    db.open({ prefix_extractor: { fixed: 3 } }, function (err) {
      t.ifError(err, 'no open error')

      db.batch()
        .put('fooA', 'A')
        .put('fooB', 'B')
        .put('fooC', 'C')
        .write(t.end.bind(t))
    })
  })

  t.test('get keys using prefix_extractor', function (t) {
    t.plan(2)

    db.get('fooA', function (err, value) {
      t.ifError(err, 'failed to get key')
      t.is(value.toString(), 'A', 'got key value')
    })
  })

  t.test('teardown', function (t) {
    db.close(t.end.bind(t))
  })

  t.end()
})
