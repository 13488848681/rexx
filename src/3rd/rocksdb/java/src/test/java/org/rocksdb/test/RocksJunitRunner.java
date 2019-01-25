
package org.rocksdb.test;

import org.junit.internal.JUnitSystem;
import org.junit.internal.RealSystem;
import org.junit.internal.TextListener;
import org.junit.runner.Description;
import org.junit.runner.JUnitCore;

import java.util.ArrayList;
import java.util.List;

/**
 * Custom Junit Runner to print also Test classes
 * and executed methods to command prompt.
 */
public class RocksJunitRunner {

  /**
   * Listener which overrides default functionality
   * to print class and method to system out.
   */
  static class RocksJunitListener extends TextListener {

    /**
     * RocksJunitListener constructor
     *
     * @param system JUnitSystem
     */
    public RocksJunitListener(JUnitSystem system) {
      super(system);
    }

    @Override
    public void testStarted(Description description) {
       System.out.format("Run: %s testing now -> %s \n",
           description.getClassName(),
           description.getMethodName());
    }
  }

  /**
   * Main method to execute tests
   *
   * @param args Test classes as String names
   */
  public static void main(String[] args){
    JUnitCore runner = new JUnitCore();
    final JUnitSystem system = new RealSystem();
    runner.addListener(new RocksJunitListener(system));
    try {
      List<Class<?>> classes = new ArrayList<>();
      for (String arg : args) {
        classes.add(Class.forName(arg));
      }
      runner.run(classes.toArray(new Class[1]));

    } catch (ClassNotFoundException e) {
      e.printStackTrace();
    }
  }
}
