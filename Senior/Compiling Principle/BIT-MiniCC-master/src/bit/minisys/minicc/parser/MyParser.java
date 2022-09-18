package bit.minisys.minicc.parser;

import MyCGrammar.MyCGrammarLexer;
import MyCGrammar.MyCGrammarParser;
import bit.minisys.minicc.MiniCCCfg;
import bit.minisys.minicc.internal.util.MiniCCUtil;
import org.antlr.v4.gui.TreeViewer;
import org.antlr.v4.runtime.ANTLRInputStream;
import org.antlr.v4.runtime.CommonTokenStream;
import org.antlr.v4.runtime.tree.ParseTree;
import org.antlr.v4.runtime.tree.ParseTreeWalker;

import java.io.FileInputStream;
import java.util.Arrays;

public class MyParser implements IMiniCCParser{
    @Override
    public String run(String iFile) throws Exception {
        String oFile = MiniCCUtil.removeAllExt(iFile) + MiniCCCfg.MINICC_PARSER_OUTPUT_EXT;

        String temp = MiniCCUtil.removeAllExt(iFile) + ".c";
        ANTLRInputStream iStream = new ANTLRInputStream(new FileInputStream(temp));
        MyCGrammarLexer lexer = new MyCGrammarLexer(iStream);
        CommonTokenStream tokens = new CommonTokenStream(lexer);

        MyCGrammarParser parser = new MyCGrammarParser(tokens);
        ParseTree tree = parser.compilationUnit();

        TreeViewer treeViewer = new TreeViewer(Arrays.asList(parser.getRuleNames()), tree);
        treeViewer.open();
        treeViewer.save(MiniCCUtil.removeAllExt(iFile) + ".png");

        ParseTreeWalker walker = new ParseTreeWalker();
        MyListener listener = new MyListener();
        listener.oFile = oFile;
        walker.walk(listener, tree);

        System.out.println("3. Parse finished!");

        return oFile;
    }
}
