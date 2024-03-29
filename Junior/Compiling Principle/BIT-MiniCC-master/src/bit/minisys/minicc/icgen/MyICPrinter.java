package bit.minisys.minicc.icgen;

import bit.minisys.minicc.parser.ast.ASTIdentifier;
import bit.minisys.minicc.parser.ast.ASTIntegerConstant;
import bit.minisys.minicc.parser.ast.ASTNode;
import bit.minisys.minicc.parser.ast.ASTStringConstant;

import java.io.FileWriter;
import java.io.IOException;
import java.util.List;

public class MyICPrinter {
    private List<Quat> quats;

    public MyICPrinter(List<Quat> quats) {
        this.quats = quats;
    }

    public void print(String filename) {
        StringBuilder sb = new StringBuilder();
        for (Quat quat : quats) {
            String op = quat.getOp();
            String res = astStr(quat.getRes());
            String opnd1 = astStr(quat.getOpnd1());
            String opnd2 = astStr(quat.getOpnd2());
            sb.append("(").append(op).append(", ").append(opnd1).append(", ").append(opnd2).append(", ").append(res).append(")\n");
        }

        try {
            FileWriter fileWriter = new FileWriter(filename);
            fileWriter.write(sb.toString());
            fileWriter.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private String astStr(ASTNode node) {
        if (node == null) {
            return "";
        } else if (node instanceof ASTIdentifier) {
            return ((ASTIdentifier) node).value;
        } else if (node instanceof ASTIntegerConstant) {
            return ((ASTIntegerConstant) node).value.toString();
        } else if (node instanceof ASTStringConstant) {
            return ((ASTStringConstant) node).value;
        } else if (node instanceof TemporaryValue) {
            return ((TemporaryValue) node).name();
        } else if (node instanceof LabelGenerator) {
            return ((LabelGenerator) node).name();
        } else {
            return "";
        }
    }
}
