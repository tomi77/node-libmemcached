// Type definitions for libmemcached
// TypeScript Version: 2.3

/**
 * @summary A memcached client.
 * @class
 */
export default class MemcachedClient {
  /**
   * Constructor.
   * @constructor
   * @param {string} config Configuration string.
   */
  constructor(config: string);

  /**
   * Store item.
   * @param {string}                   key        The key.
   * @param {Buffer | string | number} value      The value to store.
   * @param {number}                   expiration Expiration time in seconds (default 0).
   * @return {MemcachedClient}
   */
  set(key: string, value: Buffer | string | number, expiration?: number): MemcachedClient;

  /**
   * Add item. If key does exist - do nothing.
   * @param {string}                   key        The key.
   * @param {Buffer | string | number} value      The value to store.
   * @param {number}                   expiration Expiration time in seconds (default 0).
   * @return {MemcachedClient}
   */
  add(key: string, value: Buffer | string | number, expiration?: number): MemcachedClient;

  /**
   * Replace item. If key doesn't exist - do nothing.
   * @param {string}                   key        The key.
   * @param {Buffer | string | number} value      The value to store.
   * @param {number}                   expiration Expiration time in seconds (default 0).
   * @return {MemcachedClient}
   */
  replace(key: string, value: Buffer | string | number, expiration?: number): MemcachedClient;

  /**
   * Get item.
   * @param {string} key The key.
   * @return {Buffer | undefined}
   */
  get(key: string): Buffer | undefined;

  /**
   * Determine if a item exists.
   * @param {string} key The key.
   * @return {boolean}
   */
  exist(key: string): boolean;

  /**
   * Update the expiration time of an existing item without fetching it.
   * @param {string} key        The key.
   * @param {number} expiration Expiration time in seconds.
   * @return {MemcachedClient}
   */
  touch(key: string, expiration: number): MemcachedClient;

  /**
   * Remove a item.
   * @param {string} key The key.
   * @return {MemcachedClient}
   */
  delete(key: string): MemcachedClient;

  /**
   * Incrementing item.
   * @param {string} key    The key.
   * @param {number} offset The increment step (default 1).
   * @return {number}
   */
  increment(key: string, offset?: number): number;

  /**
   * Decrementing item.
   * @param {string} key    The key.
   * @param {number} offset The increment step (default 1).
   * @return {number}
   */
  decrement(key: string, offset?: number): number;
}
