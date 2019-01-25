
package org.rocksdb;

public class StatsCallbackMock implements StatisticsCollectorCallback {
  public int tickerCallbackCount = 0;
  public int histCallbackCount = 0;

  public void tickerCallback(TickerType tickerType, long tickerCount) {
    tickerCallbackCount++;
  }

  public void histogramCallback(HistogramType histType,
      HistogramData histData) {
    histCallbackCount++;
  }
}
