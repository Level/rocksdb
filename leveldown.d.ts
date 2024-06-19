// Copied from https://github.com/DefinitelyTyped/DefinitelyTyped/tree/master/types/rocksdb

/// <reference types="node" />

import {
    AbstractLevelDOWN,
    AbstractIteratorOptions,
    AbstractIterator,
    AbstractOpenOptions,
    AbstractGetOptions,
    ErrorCallback,
    ErrorValueCallback,
    AbstractChainedBatch,
    AbstractBatch,
    AbstractOptions
} from 'abstract-leveldown';

interface RocksDBCloud extends AbstractLevelDOWN<RocksDBCloud.Bytes, RocksDBCloud.Bytes> {
    open(options: RocksDBCloud.OpenOptions, cb: ErrorCallback): void;

    get(key: RocksDBCloud.Bytes, cb: ErrorValueCallback<RocksDBCloud.Bytes>): void;
    get(key: RocksDBCloud.Bytes, options: RocksDBCloud.GetOptions, cb: ErrorValueCallback<RocksDBCloud.Bytes>): void;

    put(key: RocksDBCloud.Bytes, value: RocksDBCloud.Bytes, cb: ErrorCallback): void;
    put(key: RocksDBCloud.Bytes, value: RocksDBCloud.Bytes, options: RocksDBCloud.PutOptions, cb: ErrorCallback): void;

    del(key: RocksDBCloud.Bytes, cb: ErrorCallback): void;
    del(key: RocksDBCloud.Bytes, options: RocksDBCloud.DelOptions, cb: ErrorCallback): void;

    batch(): AbstractChainedBatch<RocksDBCloud.Bytes, RocksDBCloud.Bytes>;
    batch(array: AbstractBatch[], cb: ErrorCallback): AbstractChainedBatch<RocksDBCloud.Bytes, RocksDBCloud.Bytes>;
    batch(array: AbstractBatch[], options: RocksDBCloud.BatchOptions, cb: ErrorCallback): AbstractChainedBatch<RocksDBCloud.Bytes, RocksDBCloud.Bytes>;

    approximateSize(start: RocksDBCloud.Bytes, end: RocksDBCloud.Bytes, cb: RocksDBCloud.ErrorSizeCallback): void;
    compactRange(start: RocksDBCloud.Bytes, end: RocksDBCloud.Bytes, cb: ErrorCallback): void;
    getProperty(property: string): string;
    destroy(location: string, cb: ErrorCallback): void;
    repair(location: string, cb: ErrorCallback): void;
    iterator(options?: RocksDBCloud.IteratorOptions): RocksDBCloud.Iterator;
}

declare namespace RocksDBCloud {
    type Bytes = string | Buffer;
    type ErrorSizeCallback = (err: Error | undefined, size: number) => void;
    interface OpenOptions extends AbstractOpenOptions {
        awsAccessKeyId: string;
        awsSecretAccessKey: string;
        awsRegion: string;
        awsEndpointUrl: string;
        awsBucketName: string;
        awsObjectPrefix: string;
        useSSL?: boolean | undefined;
    }

    interface GetOptions extends AbstractGetOptions {
        fillCache?: boolean | undefined;
    }

    interface PutOptions extends AbstractOptions {
        sync?: boolean | undefined;
    }

    interface DelOptions extends AbstractOptions {
        sync?: boolean | undefined;
    }

    interface BatchOptions extends AbstractOptions {
        sync?: boolean | undefined;
    }

    interface IteratorOptions extends AbstractIteratorOptions<Bytes> {
        fillCache?: boolean | undefined;
    }

    interface Iterator extends AbstractIterator<Bytes, Bytes> {
        seek(key: Bytes): void;
        binding: any;
        cache: any;
        finished: any;
        fastFuture: any;
    }

    interface Constructor {
        new(location: string): RocksDBCloud;
        (location: string): RocksDBCloud;
    }
}

declare const RocksDBCloud: RocksDBCloud.Constructor;
export default RocksDBCloud;
