package bit.minisys.minicc.icgen;

import bit.minisys.minicc.parser.ast.ASTNode;
import bit.minisys.minicc.parser.ast.ASTVisitor;

public class LabelGenerator extends ASTNode {
    private final Integer id;
    public String Type;

    public LabelGenerator(Integer id, String Type) {
        super("TemporaryValue");
        this.id = id;
        this.Type = Type;
    }

    public String name() {
        if (id == 0) {
            return "@" + Type;
        } else {
            return "@" + id + Type;
        }
    }

    @Override
    public void accept(ASTVisitor visitor) throws Exception {
    }
}
