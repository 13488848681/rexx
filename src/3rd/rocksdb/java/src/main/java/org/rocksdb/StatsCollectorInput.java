
package org.rocksdb;

/**
 * Contains all information necessary to collect statistics from one instance
 * of DB statistics.
 */
public class StatsCollectorInput {
  private final Statistics _statistics;
  private final StatisticsCollectorCallback _statsCallback;

  /**
   * Constructor for StatsCollectorInput.
   *
   * @param statistics Reference of DB statistics.
   * @param statsCallback Reference of statistics callback interface.
   */
  public StatsCollectorInput(final Statistics statistics,
      final StatisticsCollectorCallback statsCallback) {
    _statistics = statistics;
    _statsCallback = statsCallback;
  }

  public Statistics getStatistics() {
    return _statistics;
  }

  public StatisticsCollectorCallback getCallback() {
    return _statsCallback;
  }
}
