package edu.stanford.sep.seplib.corelibs.sep;
/**
 * Call seplib getch routine.
 *
 * To a large degree, the "format" argument is redundant but kept
 * to limit change.
 */
public class Getch {
    /**
     * Retrieve ints for named parameter.
     *
     * @param name   The parameter name to search for.
     * @param format The format such as "i" in which to interpret the
     *               parameter.
     * @param val    Array to hold the values retrieved, if any. The number
     *               actually retrieved is returned and will never exceed the
     *               length of this array.
     *
     * @return       The number of values returned.
     */
    public static native int getch(String name, String format, int[] val);
    /**
     * Retrieve floats for named parameter.
     *
     * @param name   The parameter name to search for.
     * @param format The format such as "f" in which to interpret the
     *               parameter.
     * @param val    Array to hold the values retrieved, if any. The number
     *               actually retrieved is returned and will never exceed the
     *               length of this array.
     *
     * @return       The number of values returned.
     */
    public static native int getch(String name, String format, float[] val);
    /**
     * Retrieve doubles for named parameter.
     *
     * @param name   The parameter name to search for.
     * @param format The format such as "g" in which to interpret the
     *               parameter.
     * @param val    Array to hold the values retrieved, if any. The number
     *               actually retrieved is returned and will never exceed the
     *               length of this array.
     *
     * @return       The number of values returned.
     */
    public static native int getch(String name, String format, double[] val);
    /**
     * Retrieve bytes for named parameter.
     *
     * @param name   The parameter name to search for.
     * @param format The format such as "s" in which to interpret the
     *               parameter.
     * @param val    Array to hold the values retrieved, if any. The number
     *               actually retrieved is returned and will never exceed the
     *               length of this array.
     *
     * @return       The number of values returned.
     *
     * Note: this is private because getch doesn't know about bytes.
     */
    private static native int getch(String name, String format, byte[] val);
    /**
     * Retrieve a String for named parameter.
     *
     * @param name   The parameter name to search for.
     * @param format The format such as "s" in which to interpret the
     *               parameter.
     * @param val    StringBuffer to hold the value retrieved, if any.
     *
     * @return       0 or 1: the number of strings returned.
     */
    public static int getch(String name, String format, StringBuffer val) {
       int rc = 0;
       byte byteBuf[] = new byte[2048];
       rc = getch(name, format, byteBuf);
       if(rc > 0) {
          byte tmpBuf[] = new byte[rc];
          System.arraycopy(byteBuf,0,tmpBuf,0,rc);
          String tmpStr = new String(tmpBuf);
          val.setLength(0);
          val.insert(0,tmpStr);
       }
       if(rc > 1) rc = 1;
       return rc;
    }
    /**
     * Supply additional command-line keyword arguments 
     *
     * @param newarg The new command line argument of the form "key=val"
     *
     * @return       0 on success
     *
     */
    public static native int getch_add_string(String newarg);

    static {
       System.loadLibrary("sep_JNI");
    }
}

