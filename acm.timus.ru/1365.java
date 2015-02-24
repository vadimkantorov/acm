// Decompiled by DJ v3.9.9.91 Copyright 2005 Atanas Neshkov  Date: 20.04.2006 22:51:59
// Home Page : http://members.fortunecity.com/neshkov/dj.html  - Check often for new version!
// Decompiler options: packimports(3) 
// Source File Name:   Parser.java

import java.io.*;
import java.util.*;

public class Parser
{
    class ExpressionStringTokenizer
    {

        public boolean hasMoreTokens()
        {
            return m_bHasMoreTokens;
        }

        public ExpressionStringToken nextToken()
        {
            ExpressionStringToken expressionstringtoken = new ExpressionStringToken(m_strCurrentToken.toString(), m_bCurrentMarker);
            m_bHasMoreTokens = parseNext();
            return expressionstringtoken;
        }

        public boolean parseNext()
        {
            if(m_iCurrentPos >= m_iExpressionLength)
                return false;
            m_bCurrentMarker = false;
            m_strCurrentToken.setLength(0);
            char c = m_arrcExpressionText[m_iCurrentPos];
            if(";()+*/".indexOf(c) >= 0)
            {
                m_strCurrentToken.append(c);
                m_iCurrentPos++;
                m_bCurrentMarker = true;
                return true;
            }
            for(; m_iCurrentPos < m_iExpressionLength; m_iCurrentPos++)
            {
                char c1 = m_arrcExpressionText[m_iCurrentPos];
                if(";()+*/".indexOf(c1) >= 0)
                    break;
                m_strCurrentToken.append(c1);
            }

            return true;
        }

        private String m_strExpressionText;
        private char m_arrcExpressionText[];
        private int m_iCurrentPos;
        private boolean m_bHasMoreTokens;
        private StringBuffer m_strCurrentToken;
        private boolean m_bCurrentMarker;
        private int m_iExpressionLength;

        ExpressionStringTokenizer(String s)
        {
            m_strCurrentToken = new StringBuffer();
            m_strExpressionText = s;
            m_arrcExpressionText = s.toCharArray();
            m_iExpressionLength = m_arrcExpressionText.length;
            m_iCurrentPos = 0;
            m_bHasMoreTokens = parseNext();
        }
    }

    class ExpressionStringToken
    {

        boolean isMarker()
        {
            return m_bIsMarker;
        }

        String getToken()
        {
            return m_strToken;
        }

        private String m_strToken;
        private boolean m_bIsMarker;

        ExpressionStringToken(String s, boolean flag)
        {
            m_strToken = s;
            m_bIsMarker = flag;
        }
    }

    class OperationIntConst extends ExpressionParserOperation
    {

        protected int execute(int ai[])
        {
            return m_iValue;
        }

        private int m_iValue;

        public OperationIntConst(int i)
        {
            m_iValue = i;
        }
    }

    class OperationConcatenateParam extends OperationConcatenate
    {

        public OperationConcatenateParam()
        {
        }
    }

    class OperationConcatenateBracket extends OperationConcatenate
    {

        public OperationConcatenateBracket()
        {
        }
    }

    class OperationConcatenate extends ExpressionParserOperation
    {

        protected int execute(int ai[])
        {
            StringBuffer stringbuffer = new StringBuffer();
            for(int i = 0; i < ai.length; i++)
                stringbuffer.append(String.valueOf(ai[i]));

            if(stringbuffer.length() == 0)
                stringbuffer.append("1");
            return Integer.valueOf(stringbuffer.toString()).intValue();
        }

        protected OperationConcatenate()
        {
        }
    }

    class OperationDiv extends ExpressionParserOperation
    {

        protected int execute(int ai[])
        {
            if(ai.length == 0)
                return 1;
            int i = ai[0];
            for(int j = 1; j < ai.length; j++)
            {
                if(ai[j] == 0)
                {
                    i = 0;
                    break;
                }
                i /= ai[j];
            }

            return i;
        }

        public OperationDiv()
        {
        }
    }

    class OperationMult extends ExpressionParserOperation
    {

        protected int execute(int ai[])
        {
            int i = 1;
            for(int j = 0; j < ai.length; j++)
                i *= ai[j];

            return i;
        }

        public OperationMult()
        {
        }
    }

    class OperationPlus extends ExpressionParserOperation
    {

        protected int execute(int ai[])
        {
            int i = 0;
            for(int j = 0; j < ai.length; j++)
                i += ai[j];

            return i;
        }

        public OperationPlus()
        {
        }
    }

    abstract class ExpressionParserOperation
    {

        public void addParameter(ExpressionParserOperation expressionparseroperation)
        {
            m_vParams.add(expressionparseroperation);
        }

        public void addParameter(int i)
        {
            addParameter(((ExpressionParserOperation) (new OperationIntConst(i))));
        }

        public int execute()
        {
            int ai[];
            if(m_vParams.size() > 0)
            {
                ai = new int[m_vParams.size()];
                for(int i = 0; i < ai.length; i++)
                    ai[i] = ((ExpressionParserOperation)m_vParams.get(i)).execute();

            } else
            {
                ai = new int[0];
            }
            return execute(ai);
        }

        public ExpressionParserOperation optimize()
        {
            for(int i = 0; i < m_vParams.size(); i++)
            {
                ExpressionParserOperation expressionparseroperation = (ExpressionParserOperation)m_vParams.get(i);
                m_vParams.set(i, expressionparseroperation.optimize());
            }

            return optimizeLocal();
        }

        public ExpressionParserOperation optimizeLocal()
        {
            return this;
        }

        protected abstract int execute(int ai[]);

        protected ArrayList m_vParams;

        ExpressionParserOperation()
        {
            m_vParams = new ArrayList();
        }
    }


    public static void main(String args[])
        throws Exception
    {

        BufferedReader bufferedreader = new BufferedReader(new InputStreamReader(System.in));
        StringBuffer stringbuffer = new StringBuffer();
        for(; bufferedreader.ready(); stringbuffer.append('\n'))
        {
            String s = bufferedreader.readLine();
            if(s == null)
                break;
            stringbuffer.append(s);
        }

        String s1 = calcExpressions(stringbuffer.toString());
        PrintWriter printwriter = new PrintWriter(new OutputStreamWriter(System.out));
        for(StringTokenizer stringtokenizer = new StringTokenizer(s1, "\r\n"); stringtokenizer.hasMoreTokens(); printwriter.println(stringtokenizer.nextToken()));
        printwriter.flush();
        printwriter.close();
    }

    private Parser()
    {
    }

    public static String calcExpressions(String s)
    {
        StringBuffer stringbuffer = new StringBuffer();
        StringTokenizer stringtokenizer = new StringTokenizer(s, "\r\n");
        int i = 0;
        String s2;
        for(; stringtokenizer.hasMoreTokens(); stringbuffer.append("Expression " + i + " evaluates to: " + s2 + "\n"))
        {
            String s1 = stringtokenizer.nextToken();
            s2 = String.valueOf(calcExpression(s1));
            i++;
        }

        return stringbuffer.toString();
    }

    public static int calcExpression(String s)
    {
        ExpressionParserOperation expressionparseroperation = prepareExpression(s);
        return expressionparseroperation.execute();
    }

    private static ExpressionParserOperation prepareExpression(String s)
    {
        Parser parser = new Parser();
        ExpressionParserOperation expressionparseroperation = parser.parseExpression(s);
        expressionparseroperation = expressionparseroperation.optimize();
        return expressionparseroperation;
    }

    public ExpressionParserOperation parseExpression(String s)
    {
        s = "(" + s + ")";
        ExpressionStringTokenizer expressionstringtokenizer = new ExpressionStringTokenizer(s);
        Stack stack = new Stack();
        stack.push(new OperationConcatenateBracket());
        while(expressionstringtokenizer.hasMoreTokens()) 
        {
            ExpressionStringToken expressionstringtoken = expressionstringtokenizer.nextToken();
            ExpressionParserOperation expressionparseroperation1 = (ExpressionParserOperation)stack.peek();
            if(!expressionstringtoken.isMarker())
            {
                int i = Integer.valueOf(expressionstringtoken.getToken()).intValue();
                expressionparseroperation1.addParameter(i);
            } else
            {
                char c = expressionstringtoken.getToken().charAt(0);
                Object obj = null;
                switch(c)
                {
                case 44: // ','
                case 45: // '-'
                case 46: // '.'
                case 48: // '0'
                case 49: // '1'
                case 50: // '2'
                case 51: // '3'
                case 52: // '4'
                case 53: // '5'
                case 54: // '6'
                case 55: // '7'
                case 56: // '8'
                case 57: // '9'
                case 58: // ':'
                default:
                    break;

                case 43: // '+'
                    stack.push(new OperationPlus());
                    stack.push(new OperationConcatenateParam());
                    break;

                case 42: // '*'
                    stack.push(new OperationMult());
                    stack.push(new OperationConcatenateParam());
                    break;

                case 47: // '/'
                    stack.push(new OperationDiv());
                    stack.push(new OperationConcatenateParam());
                    break;

                case 40: // '('
                    stack.push(new OperationConcatenateBracket());
                    stack.push(new OperationConcatenateParam());
                    break;

                case 41: // ')'
                    ExpressionParserOperation expressionparseroperation2;
                    do
                    {
                        ExpressionParserOperation expressionparseroperation5 = (ExpressionParserOperation)stack.peek();
                        stack.pop();
                        expressionparseroperation2 = (ExpressionParserOperation)stack.peek();
                        expressionparseroperation2.addParameter(expressionparseroperation5);
                    } while(!(expressionparseroperation2 instanceof OperationConcatenateBracket));
                    ExpressionParserOperation expressionparseroperation6 = (ExpressionParserOperation)stack.peek();
                    stack.pop();
                    expressionparseroperation2 = (ExpressionParserOperation)stack.peek();
                    expressionparseroperation2.addParameter(expressionparseroperation6);
                    break;

                case 59: // ';'
                    ExpressionParserOperation expressionparseroperation7;
                    do
                    {
                        expressionparseroperation7 = (ExpressionParserOperation)stack.peek();
                        stack.pop();
                        ExpressionParserOperation expressionparseroperation3 = (ExpressionParserOperation)stack.peek();
                        expressionparseroperation3.addParameter(expressionparseroperation7);
                    } while(!(expressionparseroperation7 instanceof OperationConcatenateParam));
                    stack.push(new OperationConcatenateParam());
                    break;
                }
            }
        }
        ExpressionParserOperation expressionparseroperation;
        ExpressionParserOperation expressionparseroperation4;
        for(; stack.size() > 1; expressionparseroperation4.addParameter(expressionparseroperation))
        {
            expressionparseroperation = (ExpressionParserOperation)stack.peek();
            stack.pop();
            expressionparseroperation4 = (ExpressionParserOperation)stack.peek();
        }

        return (ExpressionParserOperation)stack.peek();
    }
}