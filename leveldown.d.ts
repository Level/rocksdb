import { AbstractLevelDOWN, AbstractIterator } from 'abstract-leveldown';

declare namespace rocksdb {
  export interface RocksDB<TKey, TValue>
    extends AbstractLevelDOWN<
    TKey,
    TValue,
    RocksDBOptions,
    RocksDBPutOptions,
    RocksDBGetOptions,
    RocksDBDeleteOptions,
    RocksDBIteratorOptions<TKey, TValue>,
    RocksDBBatchOptions> {
    compactRange(start: TKey, end: TKey, cb: (err?: any) => void): void;
    getProperty(property: string): string;
    iterator(options?: RocksDBIteratorOptions<TKey, TValue>): RocksDBIterator<TKey>
    destroy(location: string, cb: (err?: any) => void): void;
    repair(location: string, cb: (err?: any) => void): void;
  }

  export interface RocksDBOptions {

  }

  export interface RocksDBPutOptions {
    sync?: boolean
  }

  export interface RocksDBGetOptions {
    fillCache?: boolean;
    asBuffer?: boolean;
  }

  export interface RocksDBDeleteOptions {
    sync?: boolean;
  }

  export interface RocksDBIteratorOptions<K, V> {
    gt?: K;
    gte?: K;
    lt?: K;
    lte?: K;
    reverse?: boolean;
    keys?: boolean;
    values?: boolean;
    limit?: number;
    keyAsBuffer?: boolean;
    valueAsBuffer?: boolean;
  }

  export interface RocksDBBatchOptions {
    sync?: boolean;
  }

  export interface RocksDBIterator<TKey> extends AbstractIterator {
    seek(key: TKey): any;
    binding: any;
    cache: any;
    finished: any;
    fastFuture: any;
  }
}
declare function rocksdb<
  TKey=any,
  TValue=any
  >(location: string)
  : rocksdb.RocksDB<TKey, TValue>;


export = rocksdb;