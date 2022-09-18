package bit.minisys.minicc.scanner;

import MyCGrammar.MyCGrammarLexer;
import bit.minisys.minicc.MiniCCCfg;
import bit.minisys.minicc.internal.util.MiniCCUtil;
import org.antlr.v4.runtime.ANTLRInputStream;
import org.antlr.v4.runtime.CommonTokenStream;

import java.io.FileInputStream;
import java.io.FileWriter;

public class MyScanner implements IMiniCCScanner{
    @Override
    public String run(String iFile) throws Exception {
        MyCGrammarLexer lexer = new MyCGrammarLexer(new ANTLRInputStream(new FileInputStream(iFile)));
        CommonTokenStream tokens = new CommonTokenStream(lexer);

        String oFile = MiniCCUtil.removeAllExt(iFile) + MiniCCCfg.MINICC_SCANNER_OUTPUT_EXT;
        FileWriter fileWriter = new FileWriter(oFile);
        for (int i = 0; i < tokens.getNumberOfOnChannelTokens(); i++) {
            fileWriter.write(tokens.get(i).toString());
            fileWriter.write("\n");
        }
        fileWriter.close();

        return oFile;
    }
}