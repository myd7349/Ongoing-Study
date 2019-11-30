namespace DragableItem
{
    using System.Diagnostics;

    public class OrderedDragableVerticalLabeledLine : DragableVerticalLabeledLine
    {
        public override bool DoCollisionDetection(DragableVerticalLabeledLine anotherVerticalLabeledLine, int xStep)
        {
            Debug.Assert(anotherVerticalLabeledLine != null);
            Debug.Assert(xStep != 0);

            int relation = string.Compare(Label, anotherVerticalLabeledLine.Label);

            // Do collison detection only when two lines are approaching.
            if (xStep > 0 && relation < 0 || xStep < 0 && relation > 0)
                return base.DoCollisionDetection(anotherVerticalLabeledLine, xStep);

            return false;
        }
    }
}
